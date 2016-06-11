/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef MQTT_UTIL_H
#define MQTT_UTIL_H

#include <string>

namespace mqtt
{

void throwIfError(const std::string &operation, int result);

}

#endif
