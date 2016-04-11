/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "ActiveApplication.h"


ActiveApplication::ActiveApplication(Application &_application) :
  active{},
  application{_application}
{
}

void ActiveApplication::timeout()
{
  active.put([this]{application.timeout();});
}

void ActiveApplication::luminosity(double value)
{
  active.put([this, value]{application.luminosity(value);});
}
