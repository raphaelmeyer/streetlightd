#include <stdio.h>
#include <stdlib.h>
#include <string>

extern "C" {
#include "platform.h"
#include "iothub_client.h"
#include "iothub_message.h"
#include "threadapi.h"
#include "crt_abstractions.h"
#include "iothubtransportamqp.h"
}

#include <protocolstack/session/Session.h>

class AMQPSession: public Session {
    public:
        AMQPSession() = default;
        virtual void setConfiguration(const SessionConfiguration &value) override;
        virtual void setUp() override;
        virtual void connect() override;
        virtual void send(const std::string& message) override;
        virtual void close() override;
        virtual void setMessageCallback(std::function<void(const std::string&)> function) override;
        //virtual IOTHUBMESSAGE_DISPOSITION_RESULT internalMessageCallback(IOTHUB_MESSAGE_HANDLE message, void* userContextCallback);
        static IOTHUBMESSAGE_DISPOSITION_RESULT internalMessageCallback(IOTHUB_MESSAGE_HANDLE message, void* userContextCallback);

    private:
        std::string connectionString{};
        IOTHUB_CLIENT_HANDLE iotHubClientHandle_; ///!< Our internal connection handle
        int receiveContext_ = 0;
        //bool(*receivedFunction_)(std::string*);
        std::function<void(const std::string&)> receivedFunction_; ///!< Function to execute on receiving
};
