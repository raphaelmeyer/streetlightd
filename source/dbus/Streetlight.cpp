/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Streetlight.h"


static const std::string DbusName{"/ch/bbv/streetlight"};
static const std::string DbusService{"ch.bbv.streetlight"};


BrightnessSensor::BrightnessSensor(DBus::Connection &connection) :
  DBus::ObjectProxy(connection, DbusName, DbusService.c_str())
{
}


LuminosityActor::LuminosityActor(DBus::Connection &connection) :
  DBus::ObjectProxy(connection, DbusName, DbusService.c_str())
{
}
