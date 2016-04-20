#include "AzureAmqp.h"

extern "C"
{
#include "platform.h"
#include "iothub_client.h"
#include "iothub_message.h"
#include "threadapi.h"
#include "crt_abstractions.h"
#include "iothubtransportamqp.h"
}

#include <exception>



/** Internal message callback which is executed when a message is received
       * @param message a handle to the message received
       * @param userContextCallback this will hold a pointer to a AMQPSession
       * @return IOTHUBMESSAGE_ACCEPTED if everything went well
       */
static IOTHUBMESSAGE_DISPOSITION_RESULT internalMessageCallback(IOTHUB_MESSAGE_HANDLE message, void* userContextCallback) {
  printf("Received a message");
  if(userContextCallback == nullptr)
    throw std::runtime_error("Error in internalMessageCallback, no callback function");

  Session::Callback *callback = reinterpret_cast<Session::Callback*>(userContextCallback);

  const unsigned char* buffer = NULL;
  size_t size = 0;

  IOTHUBMESSAGE_CONTENT_TYPE contentType = IoTHubMessage_GetContentType(message);

  if (contentType == IOTHUBMESSAGE_BYTEARRAY)
  {
    if (IoTHubMessage_GetByteArray(message, &buffer, &size) == IOTHUB_MESSAGE_OK)
    {
      //(void)printf("Received Message  with BINARY Data: <<<%.*s>>> & Size=%d\r\n",  (int)size, buffer, (int)size);
      (*callback)(std::string(reinterpret_cast<const char*>(buffer), size));
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
      (*callback)(std::string(reinterpret_cast<const char*>(buffer), size));
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

  return IOTHUBMESSAGE_ACCEPTED;
}

static void SendConfirmationCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT, void*)
{
  //printf("Successfully sent your message");
}

AzureAmqp::AzureAmqp()
{
  srand((unsigned int)time(NULL));
  if (platform_init() != 0)
  {
    throw std::runtime_error("Failed to initialize the platform");
  }
}

AzureAmqp::~AzureAmqp()
{
  platform_deinit();
}

void AzureAmqp::setConfiguration(const SessionConfiguration &value)
{
  connectionString =
      "HostName=bbvgathering.azure-devices.net;"
      "DeviceId=" + value.address + ";"
      "SharedAccessKey=" + value.credential;
}

void AzureAmqp::connect()
{
  //Try to create a connection to our endpoint
  if ((iotHubClientHandle_ = IoTHubClient_CreateFromConnectionString(connectionString.c_str(), AMQP_Protocol)) == NULL)
  {
    throw std::runtime_error("ERROR: iotHubClientHandle is NULL!\r\n");
  }

  /* Setting Message call back, so we can receive Commands. Give this pointer to callback*/
  if (IoTHubClient_SetMessageCallback((IOTHUB_CLIENT_HANDLE)iotHubClientHandle_, internalMessageCallback, &receivedFunction_) != IOTHUB_CLIENT_OK)
  {
    throw std::runtime_error("ERROR: IoTHubClient_SetMessageCallback..........FAILED!\r\n");
  }
  return;
}

void AzureAmqp::send(const std::string& message)
{
  //IOTHUB_MESSAGE_HANDLE messageHandle = IoTHubMessage_CreateFromByteArray(reinterpret_cast<const unsigned char*>(message.c_str()), strlen(message.c_str()));
  IOTHUB_MESSAGE_HANDLE messageHandle = IoTHubMessage_CreateFromString(message.c_str());
  if(messageHandle == NULL) {
    throw std::runtime_error("Couldn't create MessageHandle");
  }

  if (IoTHubClient_SendEventAsync((IOTHUB_CLIENT_HANDLE)iotHubClientHandle_, messageHandle, SendConfirmationCallback, this) != IOTHUB_CLIENT_OK)
  {
    throw std::runtime_error("ERROR: IoTHubClient_SendEventAsync..........FAILED!\r\n");
  }
  //printf("IoTHubClient_SendEventAsync accepted data for transmission to IoT Hub.\r\n");
}

void AzureAmqp::setMessageCallback(Callback function) {
  if(function == nullptr)
    std::runtime_error("No valid Message Callback");

  receivedFunction_ = function;
}

void AzureAmqp::close()
{
  IoTHubClient_Destroy((IOTHUB_CLIENT_HANDLE)iotHubClientHandle_);
  iotHubClientHandle_ = nullptr;
}

