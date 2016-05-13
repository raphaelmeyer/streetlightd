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

namespace dbus
{

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


template<typename T>
class Sensor :
    public DbusInterface<T>
{
public:
  using DbusInterface<T>::DbusInterface;
};


class BrightnessSensor :
    public Sensor<ch::bbv::brightness_proxy>
{
public:
  using Sensor<ch::bbv::brightness_proxy>::Sensor;
};


class MoistureSensor :
    public Sensor<ch::bbv::moisture_proxy>
{
public:
  using Sensor<ch::bbv::moisture_proxy>::Sensor;
};


class ProximitySensor :
    public Sensor<ch::bbv::proximity_proxy>
{
public:
  using Sensor<ch::bbv::proximity_proxy>::Sensor;
};


template<typename T>
class Actor :
    public DbusInterface<T>
{
public:
  using DbusInterface<T>::DbusInterface;
};


class LuminosityActor :
    public Actor<ch::bbv::luminosity_proxy>
{
public:
  using Actor<ch::bbv::luminosity_proxy>::Actor;
};


class WarningActor :
    public Actor<ch::bbv::warning_proxy>
{
public:
  using Actor<ch::bbv::warning_proxy>::Actor;
};

}

#endif
