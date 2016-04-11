/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef LUMINOSITYACTOR_H
#define LUMINOSITYACTOR_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-qualifiers"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "StreetlightProxy.h"
#pragma GCC diagnostic pop

#include <protocolstack/application/Actor.h>

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
