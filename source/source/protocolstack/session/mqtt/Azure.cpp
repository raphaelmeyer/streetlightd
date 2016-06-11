/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Azure.h"

#include "util.h"

namespace mqtt
{

std::string Azure::deviceId() const
{
  return configuration.user;
}

std::string Azure::receiveTopic() const
{
  return topicPrefix() + "devicebound/#";
}

std::string Azure::sendTopic() const
{
  return topicPrefix() + "events/";
}

int Azure::qos() const
{
  return 1;
}

std::string Azure::address() const
{
  return configuration.host;
}

int Azure::port() const
{
  return 8883;
}

void Azure::configure(mosqpp::mosquittopp &instance) const
{
  int value = MQTT_PROTOCOL_V311;
  throwIfError("opts_set", instance.opts_set(MOSQ_OPT_PROTOCOL_VERSION, &value));
  throwIfError("tls_set", instance.tls_set(nullptr, "/etc/ssl/certs/"));
  throwIfError("username_pw_set", instance.username_pw_set(username().c_str(), password().c_str()));
  throwIfError("tls_opts_set", instance.tls_opts_set(1, "tlsv1"));
}

void Azure::setConfiguration(const session::Configuration &value)
{
  configuration = value;
  tokenFactory = SasTokenFactory{value.password, scope()};
}

std::string Azure::scope() const
{
  return address() + "/devices/" + deviceId();
}

std::string Azure::username() const
{
  return address() + "/" + deviceId() + "/";
}

std::string Azure::password() const
{
  return tokenFactory.produce();
}

std::string Azure::topicPrefix() const
{
  return "devices/" + deviceId() + "/messages/";
}

}
