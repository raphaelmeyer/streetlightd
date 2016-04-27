#include <protocolstack/session/Session.h>

#include <string>
#include <functional>

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
  void* iotHubClientHandle_{nullptr}; ///!< Our internal connection handle
  Callback receivedFunction_; ///!< Function to execute on receiving
};
