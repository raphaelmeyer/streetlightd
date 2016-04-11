/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "protocolstack/application/Forwarder.h"
#include "protocolstack/application/ActiveApplication.h"
#include "protocolstack/presentation/KeyValueEncoder.h"
#include "protocolstack/presentation/KeyValueDecoder.h"
#include "protocolstack/session/LocalMqtt.h"
#include "protocolstack/ProtocolStack.h"
#include "protocolstack/StackFactory.h"

#include "dbus/Timer.h"
#include "dbus/BrightnessSensor.h"
#include "dbus/LuminosityActor.h"

#include "infrastructure/Queue.h"
#include "infrastructure/ActiveObject.h"
#include "infrastructure/Factory.h"
#include "infrastructure/CommandLineParser.h"

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

Configuration parseCommandline( const std::vector<std::string> &arg)
{
  Factory<Application*> applicationFactory;
  applicationFactory.add("forwarder", []{return new Forwarder();});

  Factory<Presentation::EncoderAndDecoder> encoderFactory;
  encoderFactory.add("key-value", []{ return Presentation::EncoderAndDecoder{KeyValue::encode, KeyValue::decode};});

  Factory<Session*> sessionFactory;
  sessionFactory.add("mqtt-local", []{return new LocalMqtt();});

  CommandLineParser parser{std::cout, applicationFactory, encoderFactory, sessionFactory};
  return parser.parse(arg);
}

int main(int argc, char **argv)
{
  signal(SIGTERM, niam);
  signal(SIGINT, niam);

  DBus::default_dispatcher = &dispatcher;

  const std::vector<std::string> arg{argv, argv+argc};

  Configuration configuration = parseCommandline(arg);
  ProtocolStack stack = StackFactory::produce(configuration);

  // DBus creation
  DBus::Connection connection = DBus::Connection::SessionBus();
  connection.request_name("ch.bbv.streetlightd");
  BrightnessSensor brightness{connection};
  LuminosityActor luminosity{connection};
  //TODO Timer is used for acceptance tests, use own timer when not under test
  Timer timer{connection};

  // connection
  stack.application->setBrightnessSensor([&brightness]{
    return brightness.get();
  });
  stack.application->setLuminosityActor([&luminosity](double value){
    luminosity.set(value);
  });
  timer.setCallback([&stack]{
    stack.application->timeout();
  });

  stack.session->connect();
  dispatcher.enter();
  stack.session->close();

  return 0;
}
