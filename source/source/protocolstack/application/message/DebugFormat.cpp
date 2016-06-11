/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "DebugFormat.h"

namespace message
{

DebugFormat::DebugFormat(std::ostream &_output) :
  output{_output}
{
}

void DebugFormat::incomingHeader()
{
  output << "message::Incoming(";
}

void DebugFormat::outgoingHeader()
{
  output << "message::Outgoing(";
}

void DebugFormat::footer()
{
  output << ")";
}

void DebugFormat::value(bool first, Property property, double value)
{
  write(first, property, value);
}

void DebugFormat::value(bool first, Property property, const std::string &value)
{
  write(first, property, value);
}


}
