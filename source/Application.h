/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include "Presentation.h"

class Application
{
public:
  Application(Presentation &presentation);

  void brightness(double value);

private:
  Presentation &presentation;

};

#endif
