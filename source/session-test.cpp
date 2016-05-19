/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "protocolstack/session/Factory.h"

#include <csignal>
#include <memory>
#include <iostream>

class Configuration :
    public session::Configuration
{
public:
  std::string session{};
  std::string message{};

  operator bool() const
  {
    return !session.empty();
  }
};

static Configuration parseCommandline(const std::vector<std::string> &arg, const std::set<std::string> &sessions)
{
  if (arg.size() != 6) {
    std::cout << "usage: session-test <session> <host> <user> <password> <message>" << std::endl;
    std::cout << "with session:" << std::endl;
    for (const auto& name : sessions) {
      std::cout << "  " << name << std::endl;
    }
    return {};
  }

  Configuration configuration;
  configuration.session = arg[1];
  configuration.host = arg[2];
  configuration.user = arg[3];
  configuration.password = arg[4];
  configuration.message = arg[5];

  return configuration;
}

static void waitForTermination()
{
  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGTERM);
  sigaddset(&mask, SIGINT);
  sigaddset(&mask, SIGQUIT);
  sigaddset(&mask, SIGTSTP);

  if (sigprocmask(SIG_BLOCK, &mask, nullptr) < 0) {
    perror("sigprocmask");
    return;
  }

  if (sigwaitinfo(&mask, nullptr) < 0) {
    perror("wait for exit");
  }
}

static void receiver(const presentation::Message& message)
{
  std::cout << "received message: " << message.asString() << std::endl;
}

int main(int argc, char **argv)
{
  const Factory<Session*> factory = session::factory();
  const std::vector<std::string> arg{argv, argv+argc};

  const Configuration configuration = parseCommandline(arg, factory.workers());

  if (!configuration) {
    return -1;
  }

  std::unique_ptr<Session> session{factory.produce(configuration.session)};

  session->setMessageCallback(receiver);
  session->setConfiguration(configuration);

  std::cout << "connecting to: " << configuration.host << std::endl;
  session->connect();

  std::cout << "send message: " << configuration.message << std::endl;
  session->send(configuration.message);

  std::cout << "receive messages" << std::endl;
  waitForTermination();

  std::cout << "closing" << std::endl;
  session->close();

  return 0;
}
