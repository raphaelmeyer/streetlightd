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
  return "devices/" + configuration.address + "/messages/devicebound/#";
}

std::string AzureMqtt::sendTopic() const
{
  return "devices/" + configuration.address + "/messages/events/";
}

std::string AzureMqtt::address() const
{
  return "bbvgathering.azure-devices.net";
}

int AzureMqtt::port() const
{
  return 8883;
}

void AzureMqtt::configure(mosqpp::mosquittopp &instance) const
{
  const auto username = "bbvgathering.azure-devices.net/" + deviceId();
  const auto password = configuration.credential;

  int value = MQTT_PROTOCOL_V311;
  mqtt::throwIfError("opts_set", instance.opts_set(MOSQ_OPT_PROTOCOL_VERSION, &value));
  mqtt::throwIfError("tls_set", instance.tls_set(nullptr, "/etc/ssl/certs/"));
  mqtt::throwIfError("username_pw_set", instance.username_pw_set(username.c_str(), password.c_str()));
  mqtt::throwIfError("tls_opts_set", instance.tls_opts_set(1, "tlsv1"));
}

void AzureMqtt::setConfiguration(const SessionConfiguration &value)
{
  configuration = value;
}
