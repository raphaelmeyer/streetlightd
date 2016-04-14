/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef BRIGHTNESSSENSOR_H
#define BRIGHTNESSSENSOR_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-qualifiers"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "StreetlightProxy.h"
#pragma GCC diagnostic pop

#include <dbus-c++/dbus.h>

class BrightnessSensor :
    public ch::bbv::brightness_proxy,
    public DBus::IntrospectableProxy,
    public DBus::ObjectProxy
{
public:
  BrightnessSensor(DBus::Connection& connection);

  double get();

};

#endif
