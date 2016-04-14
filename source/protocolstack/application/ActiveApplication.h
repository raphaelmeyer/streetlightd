/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef ACTIVEAPPLICATION_H
#define ACTIVEAPPLICATION_H

#include "Application.h"
#include "../infrastructure/ActiveObject.h"

#include <memory>

class ActiveApplication :
    public Application
{
public:
  ActiveApplication(std::unique_ptr<Application> &&application);

  void timeout() override;
  void received(const message::Incoming &message) override;

  void setBrightnessSensor(Sensor value) override;
  void setLuminosityActor(Actor<double> value) override;
  void setSender(Sender value) override;

private:
  ActiveObject active;
  std::unique_ptr<Application> application;

};

#endif
