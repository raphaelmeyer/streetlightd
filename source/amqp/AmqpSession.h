#include <protocolstack/session/Session.h>

#include <string>
#include <functional>

class AmqpSession :
    public Session
{
public:
  AmqpSession();
  ~AmqpSession() override;

  void setConfiguration(const SessionConfiguration &value) override;
  void connect() override;
  void send(const std::string& message) override;
  void close() override;
  void setMessageCallback(Callback function) override;

private:
  std::string connectionString{};
  void* iotHubClientHandle_{nullptr}; ///!< Our internal connection handle
  Callback receivedFunction_; ///!< Function to execute on receiving
};
