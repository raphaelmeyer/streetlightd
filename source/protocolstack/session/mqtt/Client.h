/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef AZUREMQTT_H
#define AZUREMQTT_H

#include "../Session.h"
#include "Configuration.h"

#include <mosquittopp.h>
#include <memory>

namespace mqtt
{

class Client :
    public Session,
    private mosqpp::mosquittopp
{
public:
  Client(Configuration *configuration);
  ~Client() override;

  void setConfiguration(const SessionConfiguration &value) override;

  void connect() override;
  void close() override;

  void send(const std::string &message) override;
  void setMessageCallback(Callback function) override;

private:
  std::unique_ptr<mqtt::Configuration> configuration;
  Callback listener{};

  void on_connect(int) override;
  void on_message(const struct mosquitto_message *message) override;
  void on_error() override;

};

}

#endif
