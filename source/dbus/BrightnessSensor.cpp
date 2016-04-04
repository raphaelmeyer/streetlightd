/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "BrightnessSensor.h"
#include "DbusData.h"

BrightnessSensor::BrightnessSensor(DBus::Connection &connection) :
  DBus::ObjectProxy(connection, DbusName, DbusService.c_str())
{
}

double BrightnessSensor::get()
{
  return scaled();
}
