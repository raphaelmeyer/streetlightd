/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "BrightnessSensor.h"

BrightnessSensor::BrightnessSensor(DBus::Connection &connection) :
  DBus::ObjectProxy(connection, "/StreetLight", "ch.bbv.StreetLight")
{
}

void BrightnessSensor::update(const double &value)
{
}

double BrightnessSensor::value()
{
  return this->ch::bbv::StreetLight::Brightness_proxy::value();
}
