/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "BrightnessSensor.h"
#include "MqttTest.h"

#include "Application.h"
#include "KeyValueEncoder.h"
#include "Session.h"

#include <dbus-c++/dbus.h>
#include <dbus-c++/api.h>
#include <dbus-c++-1/dbus-c++/dbus.h>


int main()
{
  DBus::BusDispatcher dispatcher;
  DBus::default_dispatcher = &dispatcher;

  MqttTest session{};
  KeyValueEncoder presentation{session};
  Application application{presentation};

  DBus::Connection connection = DBus::Connection::SessionBus();
  BrightnessSensor brightness(connection, application);

  session.start();
  dispatcher.enter();
  session.stop();

  return 0;
}
