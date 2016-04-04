/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef BRIGHTNESS_MOCK_H
#define BRIGHTNESS_MOCK_H

#include "../Brightness.h"

#include <gmock/gmock.h>

class BrightnessMock :
    public Brightness
{
public:
  MOCK_METHOD0(value, double());

};

#endif
