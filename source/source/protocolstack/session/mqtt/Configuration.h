/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef MQTTCONFIGURATION_H
#define MQTTCONFIGURATION_H

#include "../Configuration.h"

#include <mosquittopp.h>
#include <string>

namespace mqtt
{

class Configuration
{
public:
  virtual ~Configuration() = default;

  virtual std::string deviceId() const= 0;
  virtual std::string receiveTopic() const= 0;
  virtual std::string sendTopic() const= 0;
  virtual int qos() const= 0;
  virtual std::string address() const= 0;
  virtual int port() const= 0;

  virtual void configure(mosqpp::mosquittopp &instance) const= 0;

  virtual void setConfiguration(const session::Configuration &value) = 0;

};

}

#endif
