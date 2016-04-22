/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef MESSAGE_DEBUGFORMAT_H
#define MESSAGE_DEBUGFORMAT_H

#include "PrintFormat.h"
#include "Property.h"

#include <ostream>
#include <functional>
#include <string>

namespace message
{

class DebugFormat :
    public PrintFormat
{
public:
  typedef std::function<std::string(Property)> PropertyNameGetter;

  DebugFormat(std::ostream &output, PropertyNameGetter propertyName);

  void writeSeparator(bool first) override;
  void writeKey(Property key) override;
  void writeKeyValueSeparator() override;
  void writeValue(double value) override;
  void writeValue(const std::string &value) override;

private:
  std::ostream &output;
  PropertyNameGetter propertyName{};

};

}

#endif
