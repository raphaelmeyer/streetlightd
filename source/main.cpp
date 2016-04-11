/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "application/Forwarder.h"
#include "application/ActiveApplication.h"
#include "presentation/KeyValueEncoder.h"
#include "presentation/KeyValueDecoder.h"
#include "session/LocalMqtt.h"

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

class ProtocolStack
{
public:
  std::unique_ptr<Application> application;
  Presentation::Encoder encoder;
  Presentation::Decoder decoder;
  std::unique_ptr<Session> session;
};


static DBus::BusDispatcher dispatcher;

static void niam(int)
{
  dispatcher.leave();
}

ProtocolStack stackFactory(Configuration objects)
{
  ProtocolStack stack;
  stack.session = std::unique_ptr<Session>{objects.session};
  stack.encoder = objects.presentation.first;
  stack.decoder = objects.presentation.second;
  std::unique_ptr<Application> application{objects.application};
  stack.application = std::unique_ptr<ActiveApplication>{new ActiveApplication(std::move(application))};

  // connection
  stack.application->setListener([&stack](double brightness){
    const auto message = stack.encoder(brightness);
    stack.session->send(message);
  });

  stack.session->setMessageCallback([&stack](const std::string &message){
    const auto decoded = stack.decoder(message);
    stack.application->received(decoded);
  });

  return stack;
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

  Configuration objects = parseCommandline(arg);

  ProtocolStack stack = stackFactory(objects);

  // DBus creation
  DBus::Connection connection = DBus::Connection::SessionBus();
  connection.request_name("ch.bbv.streetlightd");
  BrightnessSensor brightness{connection};
  LuminosityActor luminosity{connection};

  // connection
  stack.application->setBrightnessSensor([&brightness]{
    return brightness.get();
  });
  stack.application->setLuminosityActor([&luminosity](double value){
    luminosity.set(value);
  });

  //TODO Timer is used for acceptance tests, use own timer when not under test
  Timer timer{connection, *stack.application};

  stack.session->connect();
  dispatcher.enter();
  stack.session->close();

  return 0;
}
