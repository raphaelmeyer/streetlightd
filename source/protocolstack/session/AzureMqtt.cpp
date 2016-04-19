/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "AzureMqtt.h"

AzureMqtt::AzureMqtt() :
  mosqpp::mosquittopp{}
{
  throwIfError("lib_init", mosqpp::lib_init());
}

AzureMqtt::~AzureMqtt()
{
  throwIfError("lib_cleanup", mosqpp::lib_cleanup());
}

void AzureMqtt::setConfiguration(const SessionConfiguration &value)
{
  const auto id = value.address;

  username = "bbvgathering.azure-devices.net/" + id;
  password = value.credential;
  receiveTopic = "devices/" + value.address + "/messages/devicebound/#";
  sendTopic = "devices/" + value.address + "/messages/events/";

  reinitialise(id.c_str(), true);
}

void AzureMqtt::connect()
{
  int value = MQTT_PROTOCOL_V311;
  throwIfError("opts_set", opts_set(MOSQ_OPT_PROTOCOL_VERSION, &value));
  throwIfError("tls_set", tls_set(nullptr, "/etc/ssl/certs/"));
  throwIfError("username_pw_set", username_pw_set(username.c_str(), password.c_str()));
  throwIfError("tls_opts_set", tls_opts_set(1, "tlsv1"));

  throwIfError("connect", mosqpp::mosquittopp::connect("bbvgathering.azure-devices.net", 8883));

  throwIfError("loop_start", loop_start());
}

void AzureMqtt::on_connect(int)
{
  const auto result = subscribe(nullptr, receiveTopic.c_str(), 1);
  throwIfError("subscribe", result);
}

void AzureMqtt::on_message(const mosquitto_message *message)
{
  const char *data = (const char *)message->payload;
  const std::string payload{data, data+message->payloadlen};
  listener(payload);
}

void AzureMqtt::on_error()
{
  throw std::runtime_error("undefined error in AzureMqtt");
}

void AzureMqtt::throwIfError(const std::string &operation, int result)
{
  if (result != MOSQ_ERR_SUCCESS) {
    throw std::runtime_error("AzureMqtt " + operation + ": " + mosqpp::strerror(result));
  }
}

void AzureMqtt::close()
{
  const auto stopResult = loop_stop();
  throwIfError("loop_stop", stopResult);

  const auto disconnectResult = disconnect();
  throwIfError("disconnect", disconnectResult);
}

void AzureMqtt::send(const std::string &message)
{
  const auto result = publish(nullptr, sendTopic.c_str(), message.size(), message.c_str(), 1);
  throwIfError("publish", result);
}

void AzureMqtt::setMessageCallback(Session::Callback function)
{
  listener = function;
}
