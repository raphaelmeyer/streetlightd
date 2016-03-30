/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef MQTT_H
#define MQTT_H

#include <mosquittopp.h>
#include <string>

class Mqtt :
    public mosqpp::mosquittopp
{
public:
  Mqtt(const char *id = nullptr);

  mosq_err_t connect(const std::string &host, int port = 1883);

  void on_error() override;

};

#endif
