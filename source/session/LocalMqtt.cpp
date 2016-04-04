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
  connect("localhost");
}

LocalMqtt::~LocalMqtt()
{
  disconnect();
}

void LocalMqtt::send(const std::string &message)
{
  publish(nullptr, topic.c_str(), message.size(), message.c_str(), 2, false);
}

void LocalMqtt::start()
{
  loop_start();
}

void LocalMqtt::stop()
{
  loop_stop();
}

