/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Forwarder.h"

void Forwarder::timeout()
{
  message::Outgoing message;

  message.brightness = brightnessSensor();
  message.moisture = moistureSensor();
  message.proximity = proximitySensor();

  sender(message);
}

void Forwarder::received(const message::Incoming &message)
{
  if (message.luminosity.isValid()) {
    luminosityActor(message.luminosity());
  }
  if (message.warning.isValid()) {
    warningActor(message.warning());
  }
}

void Forwarder::setBrightnessSensor(Sensor value)
{
  brightnessSensor = value;
}

void Forwarder::setMoistureSensor(Application::Sensor value)
{
  moistureSensor = value;
}

void Forwarder::setProximitySensor(Application::Sensor value)
{
  proximitySensor = value;
}

void Forwarder::setLuminosityActor(Actor<double> value)
{
  luminosityActor = value;
}

void Forwarder::setWarningActor(Actor<std::string> value)
{
  warningActor = value;
}

void Forwarder::setSender(Sender value)
{
  sender = value;
}

