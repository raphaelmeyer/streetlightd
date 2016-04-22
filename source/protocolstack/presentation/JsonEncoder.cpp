/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "JsonEncoder.h"

#include <protocolstack/application/message/propertyNames.h>
#include <protocolstack/application/message/Printer.h>
#include <protocolstack/application/message/PrintFormat.h>

#include <sstream>
#include <functional>

namespace Json
{

class Format :
    public message::PrintFormat
{
public:
  typedef std::function<std::string(message::Property)> PropertyNameGetter;

  Format(std::ostream &_output, PropertyNameGetter _propertyName) :
    output{_output},
    propertyName{_propertyName}
  {
  }

  void writeValue(double value) override
  {
    output << value;
  }

  void writeValue(const std::string &value) override
  {
    output << "\"" << value << "\"";
  }

  void writeKey(message::Property key) override
  {
    output << "\"" + propertyName(key) + "\"";
  }

  void writeKeyValueSeparator() override
  {
    output << ":";
  }

  void writeSeparator(bool first) override
  {
    if (!first) {
      output << ",";
    }
  }

private:
  std::ostream &output;
  PropertyNameGetter propertyName{};

};

presentation::Message encode(const message::Outgoing &message)
{
  // A custom serializer is written since the tested libraries do not
  // support custom float serializer.

  std::stringstream stream;
  Format format{stream, message::propertyName};
  message::Printer printer{format};

  stream << "{";
  message.accept(printer);
  stream << "}";

  return stream.str();
}

}
