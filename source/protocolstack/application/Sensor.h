/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef SENSOR_H
#define SENSOR_H

class Sensor
{
public:
  virtual ~Sensor() = default;

  virtual double get() = 0;

};

#endif
