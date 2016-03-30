/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "BrightnessSensor.h"

BrightnessSensor::BrightnessSensor(DBus::Connection &connection, SensorListener &_sensorListener) :
  DBus::ObjectProxy(connection, "/StreetLight", "ch.bbv.StreetLight.Brightness"),
  sensorListener{_sensorListener}
{
}

void BrightnessSensor::update(const double &value)
{
  sensorListener.brightness(value);
}
