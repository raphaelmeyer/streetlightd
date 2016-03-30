/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef BRIGHTNESSSENSOR_H
#define BRIGHTNESSSENSOR_H

#include "StreetlightProxy.h"
#include "SensorListener.h"

#include <dbus-c++/dbus.h>

class BrightnessSensor :
    public ch::bbv::StreetLight::Brightness_proxy,
    public DBus::IntrospectableProxy,
    public DBus::ObjectProxy
{
public:
  BrightnessSensor(DBus::Connection& connection, SensorListener &sensorListener);

  void update(const double& value) override;

private:
   SensorListener &sensorListener;
};

#endif
