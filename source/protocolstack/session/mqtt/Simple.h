/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef MQTT_SIMPLE_H
#define MQTT_SIMPLE_H

#include "Configuration.h"

namespace mqtt
{

class Simple :
    public Configuration
{
public:
  std::string deviceId() const override;
  std::string receiveTopic() const override;
  std::string sendTopic() const override;
  int qos() const override;
  std::string address() const override;
  int port() const override;

  void configure(mosqpp::mosquittopp &instance) const override;

  void setConfiguration(const session::Configuration &value) override;

private:
  session::Configuration configuration;

};

}

#endif
