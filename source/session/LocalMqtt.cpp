/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "LocalMqtt.h"

LocalMqtt::LocalMqtt() :
  mosqpp::mosquittopp{nullptr}
{
}

void LocalMqtt::send(const std::string &message)
{
  const auto result = publish(nullptr, "streetlight/sensor", message.size(), message.c_str(), 2, false);
  throwIfError("publish", result);
}

void LocalMqtt::on_message(const mosquitto_message *message)
{
  const char *data = (const char *)message->payload;
  const std::string payload{data, data+message->payloadlen};
  listener(payload);
}

void LocalMqtt::connect()
{
  const auto connectResult = mosqpp::mosquittopp::connect("localhost");
  throwIfError("connect", connectResult);

  const auto startResult = loop_start();
  throwIfError("loop_start", startResult);
}

void LocalMqtt::close()
{
  const auto stopResult = loop_stop();
  throwIfError("loop_stop", stopResult);

  const auto disconnectResult = disconnect();
  throwIfError("disconnect", disconnectResult);
}

void LocalMqtt::on_connect(int)
{
  const auto result = subscribe(nullptr, "streetlight/actor", 2);
  throwIfError("subscribe", result);
}

void LocalMqtt::on_error()
{
  throw std::runtime_error("undefined error in LocalMqtt");
}

void LocalMqtt::throwIfError(const std::string &operation, int result)
{
  if (result != MOSQ_ERR_SUCCESS) {
    throw std::runtime_error("LocalMqtt " + operation + ": " + mosqpp::strerror(result));
  }
}

void LocalMqtt::setMessageCallback(Callback function)
{
  listener = function;
}

