/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "DbusTimer.h"

DbusTimer::DbusTimer(DBus::Connection &connection) :
  DBus::ObjectAdaptor{connection, "/ch/bbv/streetlightd"}
{
}

void DbusTimer::timeout()
{
  callback();
}

void DbusTimer::setCallback(DbusTimer::Callback value)
{
  callback = value;
}
