/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef PRESENTATION_JSON_PRINTFORMAT_H
#define PRESENTATION_JSON_PRINTFORMAT_H

#include "PrintFormat.h"
#include "Message.h"

#include <protocolstack/application/message/propertyNames.h>

#include <sstream>

namespace presentation
{
namespace json
{

class PrintFormat :
    public presentation::PrintFormat
{
public:
  void incomingHeader() override;
  void outgoingHeader() override;
  void footer() override;
  void value(bool first, message::Property property, double value) override;
  void value(bool first, message::Property property, const std::string &value) override;

  presentation::Message message() const override;

private:
  std::stringstream output;

  void writeValue(double value);
  void writeValue(const std::string &value);
  void separator(bool first);

  template<typename T>
  void write(bool first, message::Property property, const T &value)
  {
    separator(first);
    output << "\"" + message::propertyName(property) + "\"";
    output << ":";
    writeValue(value);
  }

};

}
}

#endif
