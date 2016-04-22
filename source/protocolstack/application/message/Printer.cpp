/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Printer.h"

namespace message
{

Printer::Printer(PrintFormat &_format) :
  format{_format}
{
}

void Printer::visit(Property property, const Value<double> &value)
{
  print(property, value);
}

void Printer::visit(Property property, const Value<std::string> &value)
{
  print(property, value);
}

}
