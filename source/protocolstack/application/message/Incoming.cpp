/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Incoming.h"

#include "Printer.h"
#include "propertyNames.h"

namespace message
{

void Incoming::accept(Visitor &visitor) const
{
  visitor.visit(Property::Luminosity, luminosity);
  visitor.visit(Property::Warning, warning);
}

}

std::ostream& operator<<(std::ostream &stream, const message::Incoming &message)
{
  message::Printer printer{stream, message::propertyName};

  stream << "message::Incoming(";
  message.accept(printer);
  stream << ")";

  return stream;
}

