#include <cstdlib>
extern "C"
{
//#include <stdlib.h>
#ifdef _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif
//#include <stdio.h>
//#include <stdbool.h>

#include "platform.h"
#include "message_sender.h"
#include "message_receiver.h"
#include "message.h"
#include "messaging.h"
#include "amqpalloc.h"
#include "saslclientio.h"
#include "sasl_mssbcbs.h"
#include "wsio.h"
#include "consolelogger.h"
#include "cbs.h"
#include "amqp_websockets/iothub_certs.h"
}

#include <infrastructure/SasToken.h>
#include <exception>
#include <chrono>
#include <protocolstack/session/Session.h>

#include <string>
#include <memory>
#include <thread>
//#include <functional>

/**
 * Azure connection via AMQP over Websockets through azure iot sdk.
 */
class AzureAmqpWs :
        public Session
{
public:
    AzureAmqpWs();
    ~AzureAmqpWs() override;

    void setConfiguration(const session::Configuration &value) override;
    void connect() override;
    void send(const presentation::Message& message) override;
    void close() override;
    void setMessageCallback(Callback function) override;
    virtual void setAuth(bool value);
    void sentMessage();

private:
    std::string host_{};
    std::string deviceKey_{};
    std::string deviceId_{};
    bool auth_{false};
    //TODO maybe add better mechanism to tell thread to quit
    bool quitting_{false};
    unsigned int messagesPending_{0};
    //void* iotHubClientHandle_{nullptr};
    Callback receivedFunction_;

    LINK_HANDLE senderLink_;
    LINK_HANDLE receiverLink_;
    SESSION_HANDLE session_;
    CONNECTION_HANDLE connection_;
    XIO_HANDLE wsIo_;
    XIO_HANDLE saslIo_;
    SASL_MECHANISM_HANDLE saslMechanismHandle_;
    CBS_HANDLE cbs_;
    MESSAGE_SENDER_HANDLE messageSender_ = NULL;
    MESSAGE_RECEIVER_HANDLE messageReceiver_ = NULL;
    std::unique_ptr<std::thread> workerThread_{};


    //void on_cbs_operation_complete(void* context, CBS_OPERATION_RESULT cbs_operation_result, unsigned int status_code, const char* status_description);
    static AMQP_VALUE on_message_received( const void* context, MESSAGE_HANDLE message);
    static void on_amqp_management_state_chaged(void* context, AMQP_MANAGEMENT_STATE new_amqp_management_state, AMQP_MANAGEMENT_STATE previous_amqp_management_state);
    void addMessagePending();
    void doConnectionWork();

    //void on_message_send_complete(const void* context, MESSAGE_SEND_RESULT send_result);

};
