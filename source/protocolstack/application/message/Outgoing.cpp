/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Outgoing.h"

#include "Printer.h"
#include "Property.h"
#include "propertyNames.h"

namespace message
{

void Outgoing::accept(Visitor &visitor) const
{
  visitor.visit(Property::Brightness, brightness);
  visitor.visit(Property::Moisture, moisture);
  visitor.visit(Property::Info, info);
}

}

std::ostream& operator<<(std::ostream &stream, const message::Outgoing &message)
{
  message::Printer printer{stream, message::propertyName};

  stream << "message::Outgoing(";
  message.accept(printer);
  stream << ")";

  return stream;
}
