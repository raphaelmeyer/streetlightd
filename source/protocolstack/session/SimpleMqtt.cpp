/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "SimpleMqtt.h"


std::string SimpleMqtt::deviceId() const
{
  return configuration.user;
}

std::string SimpleMqtt::receiveTopic() const
{
  return "streetlight/" + configuration.user + "/actor";
}

std::string SimpleMqtt::sendTopic() const
{
  return "streetlight/" + configuration.user + "/sensor";
}

int SimpleMqtt::qos() const
{
  return 2;
}

std::string SimpleMqtt::address() const
{
  return configuration.host;
}

int SimpleMqtt::port() const
{
  return 1883;
}

void SimpleMqtt::configure(mosqpp::mosquittopp &) const
{
}

void SimpleMqtt::setConfiguration(const session::Configuration &value)
{
  configuration = value;
}
