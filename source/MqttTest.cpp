/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "MqttTest.h"

MqttTest::MqttTest() :
  mosqpp::mosquittopp{nullptr}
{
  connect("localhost");
}

MqttTest::~MqttTest()
{
  disconnect();
}

void MqttTest::send(const std::string &message)
{
  publish(nullptr, topic.c_str(), message.size(), message.c_str(), 2, false);
}

void MqttTest::start()
{
  loop_start();
}

void MqttTest::stop()
{
  loop_stop();
}

