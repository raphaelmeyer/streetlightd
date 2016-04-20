/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "protocolstack/application/Forwarder.h"
#include "protocolstack/application/Debug.h"
#include "protocolstack/application/ActiveApplication.h"
#include "protocolstack/presentation/KeyValueEncoder.h"
#include "protocolstack/presentation/KeyValueDecoder.h"
#include "protocolstack/presentation/JsonEncoder.h"
#include "protocolstack/presentation/JsonDecoder.h"
#include "protocolstack/session/AzureHttp.h"
#include "protocolstack/session/mqtt/Client.h"
#include "protocolstack/session/AzureMqtt.h"
#include "protocolstack/session/LocalMqtt.h"
#include "protocolstack/ProtocolStack.h"
#include "protocolstack/StackFactory.h"

#include "protocolstack/session/AzureAmqp.h"

#include "dbus/DbusTimer.h"
#include "dbus/Streetlight.h"

#include "infrastructure/Queue.h"
#include "infrastructure/ActiveObject.h"
#include "infrastructure/Factory.h"
#include "infrastructure/CommandLineParser.h"
#include "infrastructure/TimerFactory.h"

#include <dbus-c++/dbus.h>
#include <dbus-c++/api.h>
#include <dbus-c++-1/dbus-c++/dbus.h>

#include <csignal>
#include <memory>

static DBus::BusDispatcher dispatcher;

static void niam(int)
{
  dispatcher.leave();
}

int main(int argc, char **argv)
{
  DBus::default_dispatcher = &dispatcher;

  signal(SIGTERM, niam);
  signal(SIGINT, niam);

  const std::vector<std::string> arg{argv, argv+argc};

  Factory<Application*> applicationFactory;
  applicationFactory.add("forwarder", []{return new Forwarder();});
  applicationFactory.add("debug", []{return new Debug(std::cout);});

  Factory<Presentation::EncoderAndDecoder> encoderFactory;
  encoderFactory.add("key-value", []{ return Presentation::EncoderAndDecoder{KeyValue::encode, KeyValue::decode};});
  encoderFactory.add("json", []{ return Presentation::EncoderAndDecoder{Json::encode, Json::decode};});

  Factory<Session*> sessionFactory;
  sessionFactory.add("mqtt-local", []{return new mqtt::Client(new LocalMqtt());});
  sessionFactory.add("azure-http", []{return new AzureHttp();});
  sessionFactory.add("azure-amqp", []{return new AzureAmqp();});
  sessionFactory.add("azure-mqtt", []{return new mqtt::Client(new AzureMqtt());});

  CommandLineParser parser{std::cout};
  parser.addApplications(applicationFactory.workers());
  parser.addPresentations(encoderFactory.workers());
  parser.addSessions(sessionFactory.workers());
  Configuration configuration = parser.parse(arg);

  if (!configuration) {
    return -1;
  }

  StackFactory factory{applicationFactory, encoderFactory, sessionFactory};
  ProtocolStack stack = factory.produce(configuration);
  stack.session->setConfiguration(configuration);

  // DBus creation
  DBus::Connection connection = DBus::Connection::SessionBus();
  connection.request_name("ch.bbv.streetlightd");
  BrightnessSensor brightness{connection};
  LuminosityActor luminosity{connection};
  WarningActor warning{connection};

  //  Timer creation
  TimerFactory timerFactory{connection};
  std::unique_ptr<Timer> timer = std::unique_ptr<Timer>{timerFactory.produce(configuration)};

  // connection
  stack.application->setBrightnessSensor([&brightness]{
    return brightness.scaled();
  });
  stack.application->setLuminosityActor([&luminosity](double value){
    luminosity.scaled(value);
  });
  stack.application->setWarningActor([&warning](const std::string &value){
    warning.phrase(value);
  });
  timer->setCallback([&stack]{
    stack.application->timeout();
  });

  stack.session->connect();
  dispatcher.enter();
  stack.session->close();

  stack.application.release();

  return 0;
}
