/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef PRESENTATION_FACTORY_H
#define PRESENTATION_FACTORY_H

#include "Presentation.h"

#include <infrastructure/Factory.h>

namespace presentation
{

Factory<Presentation *> factory();

}

#endif
