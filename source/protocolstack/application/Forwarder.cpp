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

void Forwarder::received(const Incoming::Message &message)
{
  const auto luminosity = message.find(Incoming::Type::Luminosity);   //TODO use contains
  if (luminosity != message.end()) {
    luminosityActor(luminosity->second);
  }
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

