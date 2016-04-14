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

class BrightnessSensor :
    public ch::bbv::brightness_proxy,
    public DBus::IntrospectableProxy,
    public DBus::ObjectProxy
{
public:
  BrightnessSensor(DBus::Connection& connection);

};


class LuminosityActor :
    public ch::bbv::luminosity_proxy,
    public DBus::IntrospectableProxy,
    public DBus::ObjectProxy
{
public:
  LuminosityActor(DBus::Connection &connection);

};


class WarningActor :
    public ch::bbv::warning_proxy,
    public DBus::IntrospectableProxy,
    public DBus::ObjectProxy
{
public:
  WarningActor(DBus::Connection &connection);

};

#endif
