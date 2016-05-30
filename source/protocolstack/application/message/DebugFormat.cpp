/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "DebugFormat.h"

namespace message
{

DebugFormat::DebugFormat(std::ostream &_output, PropertyNameGetter _propertyName) :
  output{_output},
  propertyName{_propertyName}
{
}

void DebugFormat::writeIncomingHeader()
{
  output << "message::Incoming(";
}

void DebugFormat::writeOutgoingHeader()
{
  output << "message::Outgoing(";
}

void DebugFormat::writeFooter()
{
  output << ")";
}

void DebugFormat::writeKey(Property key)
{
  output << propertyName(key);
}

void DebugFormat::writeKeyValueSeparator()
{
  output << "=";
}

void DebugFormat::writeValue(double value)
{
  output << "\"" << std::to_string(value) << "\"";
}

void DebugFormat::writeValue(const std::string &value)
{
  output << "\"" << value << "\"";
}

void DebugFormat::writeSeparator(bool first)
{
  if (!first) {
    output << " ";
  }
}

}
