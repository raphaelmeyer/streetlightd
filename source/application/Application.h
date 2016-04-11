/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include "TimerListener.h"
#include "PresentationListener.h"

#include <functional>

class Application :
    public TimerListener,
    public PresentationListener
{
public:
  typedef std::function<double()> Sensor;
  typedef std::function<void(double)> Actor;
  typedef std::function<void(double brightness)> Listener;

  virtual void setBrightnessSensor(Sensor value) = 0;
  virtual void setLuminosityActor(Actor value) = 0;
  virtual void setListener(Listener value) = 0;

};

#endif
