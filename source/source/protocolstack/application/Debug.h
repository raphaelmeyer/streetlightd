/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef DEBUG_H
#define DEBUG_H

#include "Application.h"

#include <ostream>

/**
 * Sends debug messages to the cloud and receives messages.
 * Prints all messages to the console.
 */
class Debug :
    public Application
{
public:
  Debug(std::ostream &output);

  void timeout() override;
  void received(const message::Incoming &message) override;

  void setBrightnessSensor(Sensor) override;
  void setMoistureSensor(Sensor) override;
  void setProximitySensor(Sensor) override;
  void setLuminosityActor(Actor<double>) override;
  void setWarningActor(Actor<std::string>) override;
  void setSender(Sender value) override;

private:
  unsigned messageNr{0};
  Sender sender{};
  std::ostream &output;

};

#endif
