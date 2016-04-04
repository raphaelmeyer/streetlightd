#include "AMQPSession.h"
#include <protocolstack/session/SessionConfiguration.h>

#include <cstdio>
#include <vector>
#include <string>
#include <iostream>

void receiveFunction(std::string message, void* context) {
    printf("Received something");
}

int main(int argc, char** argv) {
  const std::vector<std::string> arg{argv, argv+argc};

  if (arg.size() != 3) {
    std::cerr << "expected: <address> <credential>" << std::endl;
    return -1;
  }
  SessionConfiguration configuration;
  configuration.address = arg[1];
  configuration.credential = arg[2];

    AMQPSession connection;
    connection.setConfiguration(configuration);
    connection.setUp();
    connection.connect();
    //std::function<void(const std::string&)> function = [](const std::string& s){ printf("Excecuting lambda with string=%s",s.c_str());};
    //connection.setMessageCallback(function);
    connection.setMessageCallback([](const std::string& s){ printf("Excecuting lambda with string=%s",s.c_str());});
    connection.send("{\"message\":\"test from Simon 2\"}");
    //connection.setMessageCallback(&receiveFunction);

getchar();
printf("Done\n");
connection.close();

return 0;
}
