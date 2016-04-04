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
   mosqpp::mosquittopp::connect("localhost");
}

LocalMqtt::~LocalMqtt()
{
  disconnect();
}

void LocalMqtt::send(const std::string &message)
{
  publish(nullptr, topic.c_str(), message.size(), message.c_str(), 2, false);
}

void LocalMqtt::setMessageCallback(Callback function)
{
  listener = function;
}

void LocalMqtt::on_connect(int)
{
  mosqpp::mosquittopp::subscribe(nullptr, "#", 2);
}

void LocalMqtt::on_message(const mosquitto_message *message)
{
  const char *data = (const char *)message->payload;
  const std::string payload{data, data+message->payloadlen};
  listener(payload);
}

void LocalMqtt::start()
{
  loop_start();
}

void LocalMqtt::stop()
{
  loop_stop();
}
