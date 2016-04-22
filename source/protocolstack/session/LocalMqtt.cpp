/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "LocalMqtt.h"


std::string LocalMqtt::deviceId() const
{
  return "LocalMqttDevice";
}

std::string LocalMqtt::receiveTopic() const
{
  return "streetlight/actor";
}

std::string LocalMqtt::sendTopic() const
{
  return "streetlight/sensor";
}

int LocalMqtt::qos() const
{
  return 2;
}

std::string LocalMqtt::address() const
{
  return "localhost";
}

int LocalMqtt::port() const
{
  return 1883;
}

void LocalMqtt::configure(mosqpp::mosquittopp &) const
{
}

void LocalMqtt::setConfiguration(const SessionConfiguration &)
{
}
