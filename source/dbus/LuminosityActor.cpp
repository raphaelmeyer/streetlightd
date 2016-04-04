/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "LuminosityActor.h"
#include "DbusData.h"

LuminosityActor::LuminosityActor(DBus::Connection &connection) :
  DBus::ObjectProxy(connection, DbusName, DbusService.c_str())
{
}

void LuminosityActor::set(double value)
{
  scaled(value);
}
