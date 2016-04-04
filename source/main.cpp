/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Timer.h"
#include "BrightnessSensor.h"
#include "MqttTest.h"

#include "Application.h"
#include "KeyValueEncoder.h"
#include "Session.h"

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

  MqttTest session{};
  KeyValueEncoder presentation{session};

  DBus::Connection connection = DBus::Connection::SessionBus();
  connection.request_name("ch.bbv.streetlightd");
  BrightnessSensor brightness(connection);

  Application application{brightness, presentation};

  Timer timer{connection, application};

  session.start();
  dispatcher.enter();
  session.stop();

  return 0;
}
