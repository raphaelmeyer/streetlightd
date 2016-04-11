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

#include <protocolstack/application/TimerListener.h>

#include <dbus-c++/dbus.h>

class Timer :
    public DBus::ObjectAdaptor,
    public DBus::IntrospectableAdaptor,
    public ch::bbv::timer_adaptor
{
public:
  Timer(DBus::Connection& connection, TimerListener &timerListener);

  void timeout() override;

private:
  TimerListener &timerListener;

};

#endif
