/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "AzureMqtt.h"

#include "mqtt/util.h"

std::string AzureMqtt::deviceId() const
{
  return configuration.address;
}

std::string AzureMqtt::receiveTopic() const
{
  return topicPrefix() + "devicebound/#";
}

std::string AzureMqtt::sendTopic() const
{
  return topicPrefix() + "events/";
}

int AzureMqtt::qos() const
{
  return 1;
}

std::string AzureMqtt::address() const
{
  return "iothubbbvgathering.azure-devices.net";
}

int AzureMqtt::port() const
{
  return 8883;
}

void AzureMqtt::configure(mosqpp::mosquittopp &instance) const
{
  int value = MQTT_PROTOCOL_V311;
  mqtt::throwIfError("opts_set", instance.opts_set(MOSQ_OPT_PROTOCOL_VERSION, &value));
  mqtt::throwIfError("tls_set", instance.tls_set(nullptr, "/etc/ssl/certs/"));
  mqtt::throwIfError("username_pw_set", instance.username_pw_set(username().c_str(), password().c_str()));
  mqtt::throwIfError("tls_opts_set", instance.tls_opts_set(1, "tlsv1"));
}

void AzureMqtt::setConfiguration(const SessionConfiguration &value)
{
  configuration = value;
  tokenFactory = SasTokenFactory{value.credential, scope()};
}

std::string AzureMqtt::scope() const
{
  return address() + "/devices/" + deviceId();
}

std::string AzureMqtt::username() const
{
  return address() + "/" + deviceId() + "/";
}

std::string AzureMqtt::password() const
{
  return tokenFactory.produce();
}

std::string AzureMqtt::topicPrefix() const
{
  return "devices/" + deviceId() + "/messages/";
}
