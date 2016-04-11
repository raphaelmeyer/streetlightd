/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Timer.h"

Timer::Timer(DBus::Connection &connection) :
  DBus::ObjectAdaptor{connection, "/ch/bbv/streetlightd"}
{
}

void Timer::timeout()
{
  callback();
}

void Timer::setCallback(Timer::Callback value)
{
  callback = value;
}
