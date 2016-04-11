/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef SENSOR_MOCK_H
#define SENSOR_MOCK_H

#include "../Sensor.h"

#include <gmock/gmock.h>

class SensorMock :
    public Sensor
{
public:
  MOCK_METHOD0(get, double());

};

#endif
