/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Simple.h"

namespace mqtt
{

std::string Simple::deviceId() const
{
  return configuration.user;
}

std::string Simple::receiveTopic() const
{
  return "streetlight/" + configuration.user + "/actor";
}

std::string Simple::sendTopic() const
{
  return "streetlight/" + configuration.user + "/sensor";
}

int Simple::qos() const
{
  return 2;
}

std::string Simple::address() const
{
  return configuration.host;
}

int Simple::port() const
{
  return 1883;
}

void Simple::configure(mosqpp::mosquittopp &) const
{
}

void Simple::setConfiguration(const session::Configuration &value)
{
  configuration = value;
}

}
