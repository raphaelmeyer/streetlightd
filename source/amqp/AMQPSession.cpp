#include "AMQPSession.h"

#include <exception>

static void SendConfirmationCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result, void* userContextCallback)
{
    //printf("Successfully sent your message");
}

void AMQPSession::setConfiguration(const SessionConfiguration &value)
{
  connectionString =
       "HostName=bbvgathering.azure-devices.net;"
       "DeviceId=" + value.address + ";"
       "SharedAccessKey=" + value.credential;
}

void AMQPSession::setUp()
{
    srand((unsigned int)time(NULL));
    if (platform_init() != 0)
    {
        //printf("Failed to initialize the platform.\r\n");
        throw std::runtime_error("Failed to initialize the platform");
    }
    return;
}

void AMQPSession::connect()
{
    //Try to create a connection to our endpoint
    if ((iotHubClientHandle_ = IoTHubClient_CreateFromConnectionString(connectionString.c_str(), AMQP_Protocol)) == NULL)
    {
        throw std::runtime_error("ERROR: iotHubClientHandle is NULL!\r\n");
    }

    /* Setting Message call back, so we can receive Commands. Give this pointer to callback*/
    if (IoTHubClient_SetMessageCallback(iotHubClientHandle_, (&AMQPSession::internalMessageCallback), this) != IOTHUB_CLIENT_OK)
    {
        throw std::runtime_error("ERROR: IoTHubClient_SetMessageCallback..........FAILED!\r\n");
    }
    return;
}

void AMQPSession::send(const std::string& message)
{
    //IOTHUB_MESSAGE_HANDLE messageHandle = IoTHubMessage_CreateFromByteArray(reinterpret_cast<const unsigned char*>(message.c_str()), strlen(message.c_str()));
    IOTHUB_MESSAGE_HANDLE messageHandle = IoTHubMessage_CreateFromString(message.c_str());
    if(messageHandle == NULL) {
        throw std::runtime_error("Couldn't create MessageHandle");
    }

    if (IoTHubClient_SendEventAsync(iotHubClientHandle_, messageHandle, SendConfirmationCallback, this) != IOTHUB_CLIENT_OK)
    {
        throw std::runtime_error("ERROR: IoTHubClient_SendEventAsync..........FAILED!\r\n");
    }
    //printf("IoTHubClient_SendEventAsync accepted data for transmission to IoT Hub.\r\n");
}

void AMQPSession::setMessageCallback(std::function<void(const std::string&)> function) {
    if(function == nullptr)
      std::runtime_error("No valid Message Callback");

    receivedFunction_ = function;
}

void AMQPSession::close()
{
    IoTHubClient_Destroy(iotHubClientHandle_);
    platform_deinit();
}

IOTHUBMESSAGE_DISPOSITION_RESULT AMQPSession::internalMessageCallback(IOTHUB_MESSAGE_HANDLE message, void* userContextCallback) {
    printf("Received a message");
    if(userContextCallback == nullptr)
        throw std::runtime_error("Error in internalMessageCallback, no \"this\" pointer");

    AMQPSession* instance = reinterpret_cast<AMQPSession*>(userContextCallback);

       const unsigned char* buffer = NULL;
       size_t size = 0;

       IOTHUBMESSAGE_CONTENT_TYPE contentType = IoTHubMessage_GetContentType(message);

       if (contentType == IOTHUBMESSAGE_BYTEARRAY)
       {
           if (IoTHubMessage_GetByteArray(message, &buffer, &size) == IOTHUB_MESSAGE_OK)
           {
               //(void)printf("Received Message  with BINARY Data: <<<%.*s>>> & Size=%d\r\n",  (int)size, buffer, (int)size);
               instance->receivedFunction_(std::string(reinterpret_cast<const char*>(buffer), size));
           }
           else
           {
               throw std::runtime_error("Failed getting the BINARY body of the message received.\r\n");
           }
       }
       else if (contentType == IOTHUBMESSAGE_STRING)
       {
           //NOTE type unsafe reinterpretation casts!
           if ((buffer = reinterpret_cast<const unsigned char*>(IoTHubMessage_GetString(message))) != NULL && (size = strlen(reinterpret_cast<const char*>(buffer))) > 0)
           {
               //(void)printf("Received Message with STRING Data: <<<%.*s>>> & Size=%d\r\n",(int)size, buffer, (int)size);
               instance->receivedFunction_(std::string(reinterpret_cast<const char*>(buffer), size));
           }
           else
           {
               throw std::runtime_error("Failed getting the STRING body of the message received.\r\n");
           }
       }
       else
       {
           //(void)printf("Failed getting the body of the message received (type %i).\r\n", contentType);
               throw std::runtime_error("Failed getting the STRING body of the message received.\r\n");
       }

       //NOTE the original azure iot client used following code to get properties from message. We might delete it in the future, if we don't need it
     /*// Retrieve properties from the message
       MAP_HANDLE mapProperties = IoTHubMessage_Properties(message);
       if (mapProperties != NULL)
       {
           const char*const* keys;
           const char*const* values;
           size_t propertyCount = 0;
           if (Map_GetInternals(mapProperties, &keys, &values, &propertyCount) == MAP_OK)
           {
               if (propertyCount > 0)
               {
                   size_t index;

                   printf("Message Properties:\r\n");
                   for (index = 0; index < propertyCount; index++)
                   {
                       printf("\tKey: %s Value: %s\r\n", keys[index], values[index]);
                   }
                   printf("\r\n");
               }
           }
       }
       */

       return IOTHUBMESSAGE_ACCEPTED;
}
