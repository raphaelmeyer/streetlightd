/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef SESSION_FACTORY_H
#define SESSION_FACTORY_H

#include "Session.h"

#include <infrastructure/Factory.h>

namespace session
{

Factory<Session*> factory();

}

#endif
