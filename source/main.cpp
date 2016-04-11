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

  Factory<Application> applicationFactory;
//  applicationFactory.add("forwarder", []{return new Forwarder();});
  applicationFactory.add("forwarder", []{return nullptr;});
  Factory<Presentation> presentationFactory;
//  presentationFactory.add("key-value", []{return new KeyValueEncoder();});
  presentationFactory.add("key-value", []{return nullptr;});
  Factory<Session> sessionFactory;
  sessionFactory.add("mqtt-local", []{return new LocalMqtt();});
  CommandLineParser parser{std::cout, applicationFactory, presentationFactory, sessionFactory};

  const std::vector<std::string> arg{argv, argv+argc};
  parser.parse(arg);

  Session *session = parser.getSession();
  KeyValueEncoder presentationEncoder{};
  presentationEncoder.setListener([&session](const std::string &message){session->send(message);});

  DBus::Connection connection = DBus::Connection::SessionBus();
  connection.request_name("ch.bbv.streetlightd");
  BrightnessSensor brightness{connection};
  LuminosityActor luminosity{connection};

  Forwarder application{brightness, luminosity, presentationEncoder};
  ActiveApplication activeApplication{application};

  KeyValueDecoder presentationDecoder{};
  presentationDecoder.setListener([&activeApplication](double luminosity){
    activeApplication.luminosity(luminosity);
  });
  session->setMessageCallback([&presentationDecoder](const std::string &message){
    presentationDecoder.decode(message);
  });

  //TODO Timer is used for acceptance tests, use own timer when not under test
  Timer timer{connection, activeApplication};

  session->connect();
  dispatcher.enter();
  session->close();

  delete session;

  return 0;
}
