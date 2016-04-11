/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef TIMER_H
#define TIMER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include "TimerAdaptor.h"
#pragma GCC diagnostic pop

#include <dbus-c++/dbus.h>

#include <functional>

class Timer :
    public DBus::ObjectAdaptor,
    public DBus::IntrospectableAdaptor,
    public ch::bbv::timer_adaptor
{
public:
  typedef std::function<void()> Callback;

  Timer(DBus::Connection& connection);

  void timeout() override;

  void setCallback(Callback value);

private:
  Callback callback;

};

#endif
