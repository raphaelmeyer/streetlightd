/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "util.h"

#include <mosquittopp.h>
#include <stdexcept>

namespace mqtt
{

void throwIfError(const std::string &operation, int result)
{
  if (result != MOSQ_ERR_SUCCESS) {
    throw std::runtime_error("MQTT " + operation + ": " + mosqpp::strerror(result));
  }
}

}
