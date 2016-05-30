/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Incoming.h"

#include "Printer.h"
#include "DebugFormat.h"
#include "propertyNames.h"

namespace message
{

void Incoming::accept(Visitor &visitor) const
{
  visitor.incomingHeader();
  visitor.visit(Property::Luminosity, luminosity);
  visitor.visit(Property::Warning, warning);
  visitor.incomingFooter();
}

}
