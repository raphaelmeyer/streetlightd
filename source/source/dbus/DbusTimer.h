/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef DBUSTIMER_H
#define DBUSTIMER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include "TimerAdaptor.h"
#pragma GCC diagnostic pop

#include <infrastructure/Timer.h>

#include <dbus-c++/dbus.h>
#include <functional>

class DbusTimer :
    public Timer,
    public DBus::ObjectAdaptor,
    public DBus::IntrospectableAdaptor,
    public ch::bbv::timer_adaptor
{
public:
  DbusTimer(DBus::Connection& connection);

  void timeout() override;

  void setCallback(Callback value) override;

private:
  Callback callback;

};

#endif
