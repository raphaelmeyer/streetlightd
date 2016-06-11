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
#include "propertyNames.h"

#include <ostream>
#include <functional>
#include <string>

namespace message
{

class DebugFormat :
    public PrintFormat
{
public:
  DebugFormat(std::ostream &output);

  void incomingHeader() override;
  void outgoingHeader() override;
  void footer() override;
  void value(bool first, Property property, double value) override;
  void value(bool first, Property property, const std::string &value) override;

private:
  std::ostream &output;

  template<typename T>
  void write(bool first, Property property, const T &value)
  {
    if (!first) {
      output << " ";
    }
    output << message::propertyName(property);
    output << "=";
    output << "\"" << value << "\"";
  }

};

}

#endif
