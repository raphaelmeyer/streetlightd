/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef LOCALMQTTCONFIGURATION_H
#define LOCALMQTTCONFIGURATION_H

#include "mqtt/Configuration.h"

class LocalMqtt :
    public mqtt::Configuration
{
public:
  std::string deviceId() const override;
  std::string receiveTopic() const override;
  std::string sendTopic() const override;
  std::string address() const override;
  int port() const override;

  void configure(mosqpp::mosquittopp &instance) const override;

  void setConfiguration(const SessionConfiguration &value) override;

};

#endif
