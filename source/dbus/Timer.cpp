/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Timer.h"

Timer::Timer(DBus::Connection &connection, TimerListener &_timerListener) :
  DBus::ObjectAdaptor{connection, "/ch/bbv/streetlightd"},
  timerListener{_timerListener}
{
}

void Timer::timeout()
{
  timerListener.timeout();
}
