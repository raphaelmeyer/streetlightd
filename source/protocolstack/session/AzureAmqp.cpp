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

static presentation::Message readAsBinary(IOTHUB_MESSAGE_HANDLE message)
{
  const unsigned char* buffer = nullptr;
  size_t size = 0;

  if (IoTHubMessage_GetByteArray(message, &buffer, &size) != IOTHUB_MESSAGE_OK)
  {
    throw std::runtime_error("Failed getting the BINARY body of the message received.\r\n");
  }

  return presentation::Message{buffer, size};
}

static presentation::Message readAsString(IOTHUB_MESSAGE_HANDLE message)
{
  const char * const string = IoTHubMessage_GetString(message);
  if (string == nullptr)
  {
    throw std::runtime_error("Failed getting the STRING body of the message received.\r\n");
  }

  return presentation::Message{string};
}

static presentation::Message convertMessage(IOTHUB_MESSAGE_HANDLE message)
{
  const auto contentType = IoTHubMessage_GetContentType(message);

  switch (contentType) {
  case IOTHUBMESSAGE_BYTEARRAY:
    return readAsBinary(message);
  case IOTHUBMESSAGE_STRING:
    return readAsString(message);
  default:
    throw std::runtime_error("Failed getting the STRING body of the message received.\r\n");
  }
}

static Session::Callback toCallback(void *ptr)
{
  if (ptr == nullptr) {
    throw std::runtime_error("Error in internalMessageCallback, no callback function");
  }

  return *reinterpret_cast<Session::Callback*>(ptr);
}

static IOTHUBMESSAGE_DISPOSITION_RESULT internalMessageCallback(IOTHUB_MESSAGE_HANDLE rawMessage, void* userContextCallback)
{
  Session::Callback callback = toCallback(userContextCallback);

  const auto message = convertMessage(rawMessage);
  callback(message);

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

void AzureAmqp::send(const presentation::Message &message)
{
  const auto content = message.asBinary();
  IOTHUB_MESSAGE_HANDLE messageHandle = IoTHubMessage_CreateFromByteArray(content.data(), content.size());
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

