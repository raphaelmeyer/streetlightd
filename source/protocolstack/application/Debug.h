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

class Debug :
    public Application
{
public:
  Debug(std::ostream &output);

  void timeout() override;
  void received(const message::Incoming &message) override;

  void setBrightnessSensor(Sensor) override;
  void setMoistureSensor(Sensor) override;
  void setLuminosityActor(Actor<double> value) override;
  void setWarningActor(Actor<std::string> value) override;
  void setSender(Sender value) override;

private:
  unsigned messageNr{0};
  Sender sender{};
  std::ostream &output;

};

#endif
