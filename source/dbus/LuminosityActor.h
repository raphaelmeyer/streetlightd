/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef LUMINOSITYACTOR_H
#define LUMINOSITYACTOR_H

#include "StreetlightProxy.h"

#include <application/Actor.h>

#include <dbus-c++/dbus.h>

class LuminosityActor :
    public ch::bbv::luminosity_proxy,
    public DBus::IntrospectableProxy,
    public DBus::ObjectProxy,
    public Actor
{
public:
  LuminosityActor(DBus::Connection &connection);

  void set(double) override;

};

#endif
