/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H

class Brightness
{
public:
  virtual ~Brightness() = default;

  virtual double value() = 0;

};

#endif
