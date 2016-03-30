/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include "SensorListener.h"
#include "Presentation.h"

class Application :
    public SensorListener
{
public:
  Application(Presentation &presentation);

  void brightness(double value) override;

private:
  Presentation &presentation;

};

#endif
