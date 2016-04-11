/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Forwarder.h"

void Forwarder::timeout()
{
  const auto brightnessValue = brightnessSensor();
  listener(brightnessValue);
}

void Forwarder::luminosity(double value)
{
  luminosityActor(value);
}

void Forwarder::setBrightnessSensor(Forwarder::Sensor value)
{
  brightnessSensor = value;
}

void Forwarder::setLuminosityActor(Forwarder::Actor value)
{
  luminosityActor = value;
}

void Forwarder::setListener(Forwarder::Listener value)
{
  listener = value;
}

