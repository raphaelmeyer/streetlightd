/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "KeyValuePrintFormat.h"

namespace presentation
{
namespace keyvalue
{

void PrintFormat::incomingHeader()
{
  output.clear();
}

void PrintFormat::outgoingHeader()
{
  incomingHeader();
}

void PrintFormat::footer()
{
}

Message PrintFormat::message() const
{
  return output.str();
}

void PrintFormat::value(bool, message::Property property, double value)
{
  write(property, value);
}

void PrintFormat::value(bool, message::Property property, const std::__cxx11::string &value)
{
  write(property, value);
}

}
}
