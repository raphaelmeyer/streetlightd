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
#include "Sensor.h"
#include "Actor.h"
#include "Presentation.h"

/**
 * Simple application logic that reads all values on a timeout and forwards it.
 * Same for receiving.
 */
class Application :
    public TimerListener,
    public PresentationListener
{
public:
  Application(Sensor &brightness_, Actor &luminosity, Presentation &presentation);

  void timeout() override;
  void luminosity(double) override;

private:
  Sensor &brightness_;
  Actor &luminosity_;
  Presentation &presentation;

};

#endif
