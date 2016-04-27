/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Offline.h"

#include <stdexcept>

void Offline::timeout()
{
  const auto luminosity = calculateLuminosity(brightnessSensor());
  luminosityActor(luminosity);
}

void Offline::received(const message::Incoming &)
{
}

void Offline::setBrightnessSensor(Sensor value)
{
  brightnessSensor = value;
}

void Offline::setMoistureSensor(Application::Sensor)
{
}

void Offline::setProximitySensor(Application::Sensor)
{
}

void Offline::setLuminosityActor(Actor<double> value)
{
  luminosityActor = value;
}

void Offline::setWarningActor(Actor<std::string>)
{
}

void Offline::setSender(Sender)
{
}

double Offline::calculateLuminosity(double brightness) const
{
  if (brightness < 0.25) {
    return 1.0;
  } else {
    return 0.0;
  }
}
