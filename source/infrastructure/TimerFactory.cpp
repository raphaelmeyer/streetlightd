/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "TimerFactory.h"
#include "InternalTimer.h"

#include <dbus/DbusTimer.h>

TimerFactory::TimerFactory(DBus::Connection &_dbus) :
  dbus{_dbus}
{
}

Timer *TimerFactory::produce(const TimerConfiguration &configuration) const
{
  if (configuration.externalTimer) {
    return new DbusTimer(dbus);
  } else {
    return new InternalTimer();
  }
}
