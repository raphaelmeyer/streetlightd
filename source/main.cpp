/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "application/Application.h"
#include "presentation/KeyValueEncoder.h"
#include "presentation/KeyValueDecoder.h"
#include "session/LocalMqtt.h"

#include "dbus/Timer.h"
#include "dbus/BrightnessSensor.h"
#include "dbus/LuminosityActor.h"

#include <dbus-c++/dbus.h>
#include <dbus-c++/api.h>
#include <dbus-c++-1/dbus-c++/dbus.h>

#include <csignal>

static DBus::BusDispatcher dispatcher;

static void niam(int)
{
  dispatcher.leave();
}

int main()
{
  signal(SIGTERM, niam);
  signal(SIGINT, niam);

  DBus::default_dispatcher = &dispatcher;

  LocalMqtt session{};
  KeyValueEncoder presentationEncoder{session};

  DBus::Connection connection = DBus::Connection::SessionBus();
  connection.request_name("ch.bbv.streetlightd");
  BrightnessSensor brightness{connection};
  LuminosityActor luminosity{connection};

  Application application{brightness, luminosity, presentationEncoder};

  KeyValueDecoder presentationDecoder{application};
  session.setMessageCallback([&presentationDecoder](const std::string &message){
    presentationDecoder.decode(message);
  });

  //TODO Timer is used for acceptance tests, use own timer when not under test
  Timer timer{connection, application};

  session.connect();
  dispatcher.enter();
  session.close();

  return 0;
}
