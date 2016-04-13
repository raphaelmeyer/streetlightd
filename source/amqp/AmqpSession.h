#include <protocolstack/session/Session.h>

extern "C"
{
#include "platform.h"
#include "iothub_client.h"
#include "iothub_message.h"
#include "threadapi.h"
#include "crt_abstractions.h"
#include "iothubtransportamqp.h"
}

#include <string>
#include <functional>

class AmqpSession :
    public Session
{
public:
  void setConfiguration(const SessionConfiguration &value) override;
  void setUp() override;
  void connect() override;
  void send(const std::string& message) override;
  void close() override;
  void setMessageCallback(Callback function) override;

  /** Internal message callback which is executed when a message is received
         * @param message a handle to the message received
         * @param userContextCallback this will hold a pointer to a AMQPSession
         * @return IOTHUBMESSAGE_ACCEPTED if everything went well
         */
  static IOTHUBMESSAGE_DISPOSITION_RESULT internalMessageCallback(IOTHUB_MESSAGE_HANDLE message, void* userContextCallback);

  std::string connectionString{};
  IOTHUB_CLIENT_HANDLE iotHubClientHandle_; ///!< Our internal connection handle
  Callback receivedFunction_; ///!< Function to execute on receiving
};
