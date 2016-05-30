/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "JsonPrintFormat.h"

namespace presentation
{
namespace json
{

void PrintFormat::incomingHeader()
{
  output.clear();
  output << "{";
}

void PrintFormat::outgoingHeader()
{
  incomingHeader();
}

void PrintFormat::footer()
{
  output << "}";
}

Message PrintFormat::message() const
{
  return output.str();
}

void PrintFormat::writeValue(double value)
{
  output << value;
}

void PrintFormat::writeValue(const std::__cxx11::string &value)
{
  output << "\"" << value << "\"";
}

void PrintFormat::separator(bool first)
{
  if (!first) {
    output << ",";
  }
}

void PrintFormat::value(bool first, message::Property property, double value)
{
  write(first, property, value);
}

void PrintFormat::value(bool first, message::Property property, const std::__cxx11::string &value)
{
  write(first, property, value);
}

}
}
