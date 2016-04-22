/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Printer.h"

namespace message
{

Printer::Printer(std::ostream &_output, PropertyNameGetter _propertyName) :
  output{_output},
  propertyName{_propertyName}
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

std::string Printer::format(double value) const
{
  return std::to_string(value);
}

std::string Printer::format(const std::string &value) const
{
  return value;
}

std::string Printer::format(const std::string &key, const std::string &value) const
{
  return key + "=" + "\"" + value + "\"";
}

std::string Printer::nextSeparator()
{
  if (first) {
    first = false;
    return "";
  } else {
    return " ";
  }
}

}
