/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "ProtocolStack.h"
#include "infrastructure/CommandLineParser.h"

#ifndef STACKFACTORY_H
#define STACKFACTORY_H

namespace StackFactory
{

ProtocolStack produce(const Configuration &configuration);

}

#endif
