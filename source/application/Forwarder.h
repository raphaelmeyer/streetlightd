/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef FORWARDER_H
#define FORWARDER_H

#include "Application.h"
#include "Sensor.h"
#include "Actor.h"
#include "Presentation.h"

/**
 * Simple application logic that reads all values on a timeout and forwards it.
 * Same for receiving.
 */
class Forwarder :
    public Application
{
public:
  Forwarder(Sensor &brightness_, Actor &luminosity, Presentation &presentation);

  void timeout() override;
  void luminosity(double) override;

private:
  Sensor &brightness_;
  Actor &luminosity_;
  Presentation &presentation;

};

#endif
