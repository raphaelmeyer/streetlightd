/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "BinaryPrintFormat.h"

#include <cmath>

namespace presentation
{
namespace binary
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
  return output;
}

void PrintFormat::writeValue(double value)
{
  output.push_back(uint8_t(std::round(value * 100)));
}

void PrintFormat::writeValue(const std::__cxx11::string &value)
{
  output.push_back(value.size());
  output.insert(output.end(), value.begin(), value.end());
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
