/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Application.h"

Application::Application(Sensor &_brightness, Actor &_luminosity, Presentation &_presentation) :
  brightness_{_brightness},
  luminosity_{_luminosity},
  presentation{_presentation}
{
}

void Application::timeout()
{
  const auto brightnessValue = brightness_.get();
  presentation.brightness(brightnessValue);
}

void Application::luminosity(double value)
{
  luminosity_.set(value);
}
