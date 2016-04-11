/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef FORWARDER_H
#define FORWARDER_H

#include "Application.h"

#include <functional>

/**
 * Simple application logic that reads all values on a timeout and forwards it.
 * Same for receiving.
 */
class Forwarder :
    public Application
{
public:
  typedef std::function<double()> Sensor;
  typedef std::function<void(double)> Actor;
  typedef std::function<void(double brightness)> Listener;

  void timeout() override;
  void luminosity(double) override;

  void setBrightnessSensor(Sensor value);
  void setLuminosityActor(Actor value);
  void setListener(Listener value);

private:
  Sensor brightnessSensor{};
  Actor luminosityActor{};
  Listener listener{};

};

#endif
