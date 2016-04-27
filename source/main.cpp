/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */


#include "protocolstack/application/ActiveApplication.h"
#include "protocolstack/application/Debug.h"
#include "protocolstack/application/Forwarder.h"
#include "protocolstack/presentation/BinaryDecoder.h"
#include "protocolstack/presentation/BinaryEncoder.h"
#include "protocolstack/presentation/JsonDecoder.h"
#include "protocolstack/presentation/JsonEncoder.h"
#include "protocolstack/presentation/KeyValueDecoder.h"
#include "protocolstack/presentation/KeyValueEncoder.h"
#include "protocolstack/presentation/Null.h"
#include "protocolstack/session/AzureAmqp.h"
#include "protocolstack/session/AzureHttp.h"
#include "protocolstack/session/AzureMqtt.h"
#include "protocolstack/session/SimpleMqtt.h"
#include "protocolstack/session/mqtt/Client.h"
#include "protocolstack/session/Null.h"

#include "protocolstack/ProtocolStack.h"
#include "protocolstack/StackFactory.h"

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

  Factory<presentation::EncoderAndDecoder> encoderFactory;
  encoderFactory.add("none", []{ return presentation::EncoderAndDecoder{presentation::null::encode, presentation::null::decode};});
  encoderFactory.add("binary", []{ return presentation::EncoderAndDecoder{Binary::encode, Binary::decode};});
  encoderFactory.add("key-value", []{ return presentation::EncoderAndDecoder{KeyValue::encode, KeyValue::decode};});
  encoderFactory.add("json", []{ return presentation::EncoderAndDecoder{Json::encode, Json::decode};});

  Factory<Session*> sessionFactory;
  sessionFactory.add("none", []{return new session::Null();});
  sessionFactory.add("azure-amqp", []{return new AzureAmqp();});
  sessionFactory.add("azure-http", []{return new AzureHttp();});
  sessionFactory.add("azure-mqtt", []{return new mqtt::Client(new AzureMqtt());});
  sessionFactory.add("simple-mqtt", []{return new mqtt::Client(new SimpleMqtt());});

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
  MoistureSensor moisture{connection};
  ProximitySensor proximity{connection};
  LuminosityActor luminosity{connection};
  WarningActor warning{connection};

  //  Timer creation
  TimerFactory timerFactory{connection};
  std::unique_ptr<Timer> timer = std::unique_ptr<Timer>{timerFactory.produce(configuration)};

  // connection
  stack.application->setBrightnessSensor([&brightness]{
    return brightness.scaled();
  });
  stack.application->setMoistureSensor([&moisture]{
    return moisture.scaled();
  });
  stack.application->setProximitySensor([&proximity]{
    return proximity.scaled();
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
