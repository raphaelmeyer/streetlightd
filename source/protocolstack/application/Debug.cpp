/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Debug.h"

Debug::Debug(std::ostream &_output) :
  output{_output}
{
}

void Debug::timeout()
{
  messageNr++;

  message::Outgoing message{};
  message.info = "debug message number " + std::to_string(messageNr);
  sender(message);

  output << message << std::endl;
}

void Debug::received(const message::Incoming &message)
{
  output << message << std::endl;
}

void Debug::setBrightnessSensor(Sensor)
{
}

void Debug::setLuminosityActor(Actor<double>)
{
}

void Debug::setWarningActor(Actor<std::string>)
{
}

void Debug::setSender(Sender value)
{
  sender = value;
}

