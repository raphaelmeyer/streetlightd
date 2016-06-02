extern "C" {
#include "session.h"
}
#include "AzureAmqpWs.h"
#include <thread>

//TODO move as much .h files here as possible
//TODO not everything is multithread safe
//TODO how to handle error conditions - now just throwing
//TODO where to do connection_dowork (thread?)

extern const char iothub_certs[];

const long saslExpirationTime = 60 * 60 * 24 * 365 * 10; //expiration 10 years

static presentation::Message convertMessage(MESSAGE_HANDLE message)
{
    BINARY_DATA data;
    message_get_body_amqp_data(message, 0, &data);
    return presentation::Message{data.bytes, data.length};
}
static Session::Callback toCallback( void *ptr)
{
    if (ptr == nullptr) {
        throw std::runtime_error("Error in internalMessageCallback, no callback function");
    }

    return *reinterpret_cast<Session::Callback*>(ptr);
}


AMQP_VALUE AzureAmqpWs::on_message_received(const void* context, MESSAGE_HANDLE rawMessage)
{
    Session::Callback callback = toCallback(const_cast<void*>(context));

    const auto message = convertMessage(rawMessage);
    callback(message);

    return messaging_delivery_accepted();
}

void AzureAmqpWs::on_amqp_management_state_chaged(void* /*context*/, AMQP_MANAGEMENT_STATE new_amqp_management_state, AMQP_MANAGEMENT_STATE /*previous_amqp_management_state*/)
{

    if (new_amqp_management_state == AMQP_MANAGEMENT_STATE_IDLE)
    {
        printf("Disconnected.\r\n");
    }
}

void AzureAmqpWs::addMessagePending()
{
    //TODO not multithread safe
    messagesPending_++;
}

void AzureAmqpWs::doConnectionWork()
{
    //SESSION_INSTANCE_TAG* session_instance = (SESSION_INSTANCE_TAG*)session_;
    while(!quitting_) {
        connection_dowork(connection_);
    }
    printf("Closing up thread\n");
}

void AzureAmqpWs::setAuth(bool value)
{
    this->auth_ = value;
}

void AzureAmqpWs::sentMessage()
{
    //TODO make multithread safe
    if(messagesPending_>0)
        --messagesPending_;
}

void on_message_send_complete(void* context, MESSAGE_SEND_RESULT send_result)
{
    AzureAmqpWs* instance = static_cast<AzureAmqpWs*>(context);
    if(send_result == MESSAGE_SEND_OK)
        instance->sentMessage();
    else
        throw std::runtime_error("could not send the last message");
}

void on_cbs_operation_complete(void* context, CBS_OPERATION_RESULT cbs_operation_result, unsigned int /*status_code*/, const char* /*status_description*/)
{
    AzureAmqpWs* instance = static_cast<AzureAmqpWs*>(context);
    if(!instance)
        throw std::runtime_error("No context given on Auth finished at");
    if (cbs_operation_result == CBS_OPERATION_RESULT_OK)
        instance->setAuth(true);
    else
        throw std::runtime_error("Error in on_cbs_operation complete at"+__LINE__);
}

AzureAmqpWs::AzureAmqpWs()
{

}

AzureAmqpWs::~AzureAmqpWs()
{

}

void AzureAmqpWs::setConfiguration(const session::Configuration &value)
{
    host_ = value.host;
    deviceKey_ = value.password;
    deviceId_ = value.user;
}

void AzureAmqpWs::connect()
{

    /* create SASL MSSBCBS handler */
    saslMechanismHandle_ = saslmechanism_create(saslmssbcbs_get_interface(), NULL);

    std::string scope(host_+"%2fdevices%2f"+deviceId_);
    SasTokenFactory sastoken(deviceKey_, scope , saslExpirationTime);

    /* create the TLS IO */
    WSIO_CONFIG ws_io_config = { host_.c_str(), 443, "AMQPWSB10",  "/$iothub/websocket", true, iothub_certs };
    const IO_INTERFACE_DESCRIPTION* tlsio_interface = wsio_get_interface_description();
    wsIo_ = xio_create(tlsio_interface, &ws_io_config, NULL);

    /* create the SASL IO using the WS IO */
    SASLCLIENTIO_CONFIG sasl_io_config = { wsIo_, saslMechanismHandle_ };
    saslIo_ = xio_create(saslclientio_get_interface_description(), &sasl_io_config, NULL);

    /* create the connection, session and link */
    connection_ = connection_create(saslIo_, host_.c_str(), "some", NULL, NULL);
    session_ = session_create(connection_, NULL, NULL);
    session_set_incoming_window(session_, 2147483647);
    session_set_outgoing_window(session_, 65536);

    //printf("Creating cbs\n");
    cbs_ = cbs_create(session_, NULL, NULL);
    if (cbs_open(cbs_) == 0)
    {
        //printf("cbs open success\n");
        sastoken.produce().c_str();
        cbs_put_token(cbs_, "servicebus.windows.net:sastoken", (host_+"/devices/"+deviceId_).c_str(), sastoken.produce().c_str() , on_cbs_operation_complete, this);
        while (!auth_)
        {
            connection_dowork(connection_);
        }
        //printf("Have auth_\n");
    }


    /* set incoming window to 100 for the session */
    session_set_incoming_window(session_, 100);
    AMQP_VALUE rcvsource = messaging_create_source( ("amqps://"+host_ +"/devices/"+ deviceId_ +"/messages/devicebound").c_str());
    AMQP_VALUE rcvtarget = messaging_create_target("ingress-rx");
    receiverLink_ = link_create(session_, "receiver-link", role_receiver, rcvsource, rcvtarget);
    if(!receiverLink_)
        throw std::runtime_error("Error in creating receiver link at "+__LINE__);
    link_set_rcv_settle_mode(receiverLink_, receiver_settle_mode_first);
    (void)link_set_max_message_size(receiverLink_, 65536);

    AMQP_VALUE source = messaging_create_source("ingress");
    AMQP_VALUE target = messaging_create_target(("amqps://"+host_ +"/devices/"+ deviceId_+ "/messages/events").c_str());
    senderLink_ = link_create(session_, "sender-link", role_sender, source, target);
    if(!senderLink_)
        throw std::runtime_error("Error in creating sender link at "+__LINE__);

    amqpvalue_destroy(source);
    amqpvalue_destroy(target);
    amqpvalue_destroy(rcvsource);
    amqpvalue_destroy(rcvtarget);
    messageSender_ = messagesender_create(senderLink_, NULL, NULL, NULL);
    /* Message receiver seems to have to be created before sender, else connection_dowork doesn't seem to function properly */
    messageReceiver_ = messagereceiver_create(receiverLink_, NULL, NULL);

    if ((messageReceiver_ == NULL) ||
            (messagereceiver_open(messageReceiver_, on_message_received, &receivedFunction_) != 0))
    {
        std::runtime_error("Couldn't open message receiver at"+__LINE__);
    }
    if(messageReceiver_ != NULL)
    {
        //TODO in own thread or repeatedly executed?
       // connection_dowork(connection_);

    }
    workerThread_ = std::make_unique<std::thread>(&AzureAmqpWs::doConnectionWork, this);

    return;
}

void AzureAmqpWs::send(const presentation::Message &message)
{
    MESSAGE_HANDLE messageHandle = message_create();
    /* create a message sender */
    std::string messageString = message.asString();

    //TODO investigate why following does not work / make it work for binary data
    //const unsigned char *message_content{message.asBinary().data()};
    const unsigned char *message_content{reinterpret_cast <unsigned char const *>(messageString.c_str())};

    size_t message_size = message.asBinary().size();
    BINARY_DATA binary_data = { message_content, message_size };
    message_add_body_amqp_data(messageHandle, binary_data);

    if(!messageSender_)
        throw std::runtime_error("MessageSender is not defined at "+__LINE__);

    //printf("Opening message sender\n");
    if (messagesender_open(messageSender_) == 0)
    {
        messagesender_send(messageSender_, messageHandle, on_message_send_complete, this);
        addMessagePending();

        //TODO: connection_dowork maybe in own thread
        //while(messagesPending_ > 0)
         //  connection_dowork(connection_);
        message_destroy(messageHandle);
    }
    else
    {
        throw std::runtime_error("Couldn't open message sender");
    }
}

void AzureAmqpWs::setMessageCallback(Callback function) {
    if(function == nullptr)
        std::runtime_error("No valid Message Callback");

    receivedFunction_ = function;
}

void AzureAmqpWs::close()
{
    quitting_ = true;
    messagesender_destroy(messageSender_);
    messagereceiver_destroy(messageReceiver_);
    cbs_destroy(cbs_);
    link_destroy(senderLink_);
    session_destroy(session_);
    //workerThread_.reset();
    workerThread_->join();
    connection_destroy(connection_);
    xio_destroy(saslIo_);
    xio_destroy(wsIo_);
    saslmechanism_destroy(saslMechanismHandle_);
    platform_deinit();
}

