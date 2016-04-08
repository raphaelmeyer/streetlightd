/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef MQTTTEST_H
#define MQTTTEST_H

#include <presentation/Session.h>

#include <mosquittopp.h>

#include <string>
#include <functional>

/**
 * Simple mqtt session implementation that connects to a local mqtt server.
 */
class LocalMqtt :
    public Session,
    private mosqpp::mosquittopp
{
public:
  LocalMqtt();

  void send(const std::string &message) override;

  void setUp() override {}
  void connect() override;
  void close() override;

  void setMessageCallback(Callback function) override;

private:
  Callback listener{};

  void on_connect(int) override;
  void on_message(const struct mosquitto_message *message) override;
  void on_error() override;

  void throwIfError(const std::string &operation, int result);

};

#endif
