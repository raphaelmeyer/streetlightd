#include <protocolstack/session/Session.h>

#include <string>
#include <functional>

/**
 * Azure connection via AMQP through azure iot sdk.
 */
class AzureAmqp :
    public Session
{
public:
  AzureAmqp();
  ~AzureAmqp() override;

  void setConfiguration(const session::Configuration &value) override;
  void connect() override;
  void send(const presentation::Message& message) override;
  void close() override;
  void setMessageCallback(Callback function) override;

private:
  std::string connectionString{};
  void* iotHubClientHandle_{nullptr};
  Callback receivedFunction_;
};
