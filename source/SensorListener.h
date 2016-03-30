/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef SENSORLISTENER
#define SENSORLISTENER

class SensorListener
{
public:
  virtual ~SensorListener() = default;

  virtual void brightness(double value) = 0;

};

#endif

