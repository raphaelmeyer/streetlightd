/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "TimerFactory.h"

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
    throw std::runtime_error("internal timer not yet implemented");
  }
}
