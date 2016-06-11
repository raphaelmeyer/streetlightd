/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Printer.h"

#include "Incoming.h"
#include "Outgoing.h"

namespace message
{

Printer::Printer(PrintFormat &_format) :
  format{_format}
{
}

void Printer::incomingHeader()
{
  format.incomingHeader();
}

void Printer::incomingFooter()
{
  format.footer();
}

void Printer::outgoingHeader()
{
  format.outgoingHeader();
}

void Printer::outgoingFooter()
{
  format.footer();
}

void Printer::property(Property property, const Value<double> &value)
{
  write(property, value);
}

void Printer::property(Property property, const Value<std::string> &value)
{
  write(property, value);
}

}
