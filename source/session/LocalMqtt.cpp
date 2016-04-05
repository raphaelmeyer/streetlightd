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
  const auto result = mosqpp::mosquittopp::connect("localhost");
  throwIfError("connect", result);
}

LocalMqtt::~LocalMqtt()
{
  const auto result = disconnect();
  throwIfError("disconnect", result);
}

void LocalMqtt::send(const std::string &message)
{
  const auto result = publish(nullptr, "streetlight/sensor", message.size(), message.c_str(), 2, false);
  throwIfError("publish", result);
}

void LocalMqtt::setMessageCallback(Callback function)
{
  listener = function;
}

void LocalMqtt::on_connect(int)
{
  const auto result = subscribe(nullptr, "streetlight/actor", 2);
  throwIfError("subscribe", result);
}

void LocalMqtt::on_message(const mosquitto_message *message)
{
  const char *data = (const char *)message->payload;
  const std::string payload{data, data+message->payloadlen};
  listener(payload);
}

void LocalMqtt::start()
{
  const auto result = loop_start();
  throwIfError("loop_start", result);
}

void LocalMqtt::stop()
{
  const auto result = loop_stop();
  throwIfError("loop_stop", result);
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

