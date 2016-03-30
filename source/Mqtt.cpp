/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Mqtt.h"

#include <iostream>

Mqtt::Mqtt(const char *id) :
  mosqpp::mosquittopp{id}
{
}

mosq_err_t Mqtt::connect(const std::string &host, int port)
{
  return mosq_err_t(mosqpp::mosquittopp::connect(host.c_str(), port));
}

void Mqtt::on_error()
{
  std::cerr << __func__ << std::endl;
}
