/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef STREETLIGHT_H
#define STREETLIGHT_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-qualifiers"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "StreetlightProxy.h"
#pragma GCC diagnostic pop

#include <dbus-c++/dbus.h>

template<typename T>
class DbusInterface :
    public T,
    public DBus::IntrospectableProxy,
    public DBus::ObjectProxy
{
public:
  DbusInterface(DBus::Connection& connection) :
    DBus::ObjectProxy(connection, "/ch/bbv/streetlight", "ch.bbv.streetlight")
  {
  }
};

typedef DbusInterface<ch::bbv::brightness_proxy>  BrightnessSensor;
typedef DbusInterface<ch::bbv::moisture_proxy>    MoistureSensor;
typedef DbusInterface<ch::bbv::luminosity_proxy>  LuminosityActor;
typedef DbusInterface<ch::bbv::warning_proxy>     WarningActor;

#endif
