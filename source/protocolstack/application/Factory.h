/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef APPLICATION_FACTORY_H
#define APPLICATION_FACTORY_H

#include <infrastructure/Factory.h>

#include "Application.h"

namespace application
{

Factory<Application*> factory();

}

#endif
