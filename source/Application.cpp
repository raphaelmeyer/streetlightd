/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Application.h"

Application::Application(Brightness &_brightness, Presentation &_presentation) :
  brightness_{_brightness},
  presentation{_presentation}
{
}

void Application::timeout()
{
  const auto brightnessValue = brightness_.value();
  presentation.brightness(brightnessValue);
}
