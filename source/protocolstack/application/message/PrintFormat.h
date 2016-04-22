/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef MESSAGE_PRINTFORMAT_H
#define MESSAGE_PRINTFORMAT_H

#include "Property.h"

#include <string>

namespace message
{

class PrintFormat
{
public:
  virtual ~PrintFormat() = default;

  virtual void writeSeparator(bool first) = 0;
  virtual void writeKey(message::Property key) = 0;
  virtual void writeKeyValueSeparator() = 0;
  virtual void writeValue(double value) = 0;
  virtual void writeValue(const std::string &value) = 0;

};

}

#endif
