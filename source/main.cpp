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

int main(int argc, char **argv)
{
  signal(SIGTERM, niam);
  signal(SIGINT, niam);

  DBus::default_dispatcher = &dispatcher;

  Factory<Application*> applicationFactory;
  applicationFactory.add("forwarder", []{return new Forwarder();});
  Factory<Presentation::EncoderAndDecoder> encoderFactory;
  encoderFactory.add("key-value", []{ return Presentation::EncoderAndDecoder{KeyValue::encode, KeyValue::decode};});
  Factory<Session*> sessionFactory;
  sessionFactory.add("mqtt-local", []{return new LocalMqtt();});
  CommandLineParser parser{std::cout, applicationFactory, encoderFactory, sessionFactory};

  const std::vector<std::string> arg{argv, argv+argc};
  parser.parse(arg);

  // Stack creation
  std::unique_ptr<Session> session{parser.getSession()};
  Presentation::Encoder encoder = parser.getPresentation().first;
  Presentation::Decoder decoder = parser.getPresentation().second;
  std::unique_ptr<Application> application{parser.getApplication()};
  ActiveApplication activeApplication{std::move(application)};

  // DBus creation
  DBus::Connection connection = DBus::Connection::SessionBus();
  connection.request_name("ch.bbv.streetlightd");
  BrightnessSensor brightness{connection};
  LuminosityActor luminosity{connection};

  // connection
  activeApplication.setBrightnessSensor([&brightness]{
    return brightness.get();
  });
  activeApplication.setLuminosityActor([&luminosity](double value){
    luminosity.set(value);
  });
  activeApplication.setListener([encoder, &session](double brightness){
    const auto message = encoder(brightness);
    session->send(message);
  });

  session->setMessageCallback([decoder, &activeApplication](const std::string &message){
    const auto decoded = decoder(message);
    activeApplication.received(decoded);
  });


  //TODO Timer is used for acceptance tests, use own timer when not under test
  Timer timer{connection, activeApplication};

  session->connect();
  dispatcher.enter();
  session->close();

  return 0;
}
