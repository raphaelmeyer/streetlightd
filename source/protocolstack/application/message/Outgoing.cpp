/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Outgoing.h"

#include "Printer.h"
#include "DebugFormat.h"
#include "Property.h"
#include "propertyNames.h"

namespace message
{

void Outgoing::accept(Visitor &visitor) const
{
  visitor.outgoingHeader();
  visitor.property(Property::Brightness, brightness);
  visitor.property(Property::Moisture, moisture);
  visitor.property(Property::Proximity, proximity);
  visitor.property(Property::Info, info);
  visitor.outgoingFooter();
}

}
