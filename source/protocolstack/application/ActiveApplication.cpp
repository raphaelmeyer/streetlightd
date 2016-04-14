/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "ActiveApplication.h"


ActiveApplication::ActiveApplication(std::unique_ptr<Application> &&_application) :
  active{},
  application{std::move(_application)}
{
}

void ActiveApplication::timeout()
{
  active.put([this]{application->timeout();});
}

void ActiveApplication::received(const message::Incoming &message)
{
  active.put([this, message]{application->received(message);});
}

void ActiveApplication::setBrightnessSensor(Application::Sensor value)
{
  application->setBrightnessSensor(value);
}

void ActiveApplication::setLuminosityActor(Application::Actor value)
{
  application->setLuminosityActor(value);
}

void ActiveApplication::setSender(Application::Sender value)
{
  application->setSender(value);
}
