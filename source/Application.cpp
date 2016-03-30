/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Application.h"

Application::Application(Presentation &_presentation) :
  presentation{_presentation}
{
}

void Application::brightness(double value)
{
  presentation.brightness(value);
}
