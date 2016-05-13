/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef MQTT_AZURE_H
#define MQTT_AZURE_H

#include "Configuration.h"

#include <infrastructure/SasToken.h>

namespace mqtt
{

class Azure :
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
  SasTokenFactory tokenFactory{"", ""};

  std::string scope() const;
  std::string username() const;
  std::string password() const;
  std::string topicPrefix() const;

};

}

#endif
