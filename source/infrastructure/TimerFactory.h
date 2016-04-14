/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef TIMERFACTORY_H
#define TIMERFACTORY_H

#include "Timer.h"
#include "TimerConfiguration.h"

#include <dbus-c++/connection.h>

class TimerFactory
{
public:
  TimerFactory(DBus::Connection &dbus);

  Timer *produce(const TimerConfiguration &configuration) const;

private:
  DBus::Connection &dbus;

};

#endif
