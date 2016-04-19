/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef AZUREMQTT_H
#define AZUREMQTT_H

#include "Session.h"

#include <mosquittopp.h>

class AzureMqtt :
    public Session,
    private mosqpp::mosquittopp
{
public:
  AzureMqtt();
  ~AzureMqtt() override;

  void setConfiguration(const SessionConfiguration &value) override;

  void connect() override;
  void close() override;

  void send(const std::string &message) override;
  void setMessageCallback(Callback function) override;

private:
  std::string username{"bbvgathering.azure-devices.net/Device2"};
  std::string password{};
  std::string receiveTopic{"devices/Device2/messages/devicebound/#"};
  std::string sendTopic{"devices/Device2/messages/events/"};
  Callback listener{};

  void on_connect(int) override;
  void on_message(const struct mosquitto_message *message) override;
  void on_error() override;

  void throwIfError(const std::string &operation, int result);

};

#endif
