/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef OFFLINE_H
#define OFFLINE_H

#include "Application.h"

#include <functional>

class Offline :
    public Application
{
public:
  void timeout() override;
  void received(const message::Incoming &message) override;

  void setBrightnessSensor(Sensor value) override;
  void setMoistureSensor(Sensor value) override;
  void setProximitySensor(Sensor value) override;
  void setLuminosityActor(Actor<double> value) override;
  void setWarningActor(Actor<std::string> value) override;
  void setSender(Sender value) override;

private:
  Sensor brightnessSensor{};
  Actor<double> luminosityActor{};

  double calculateLuminosity(double brightness) const;

};

#endif
