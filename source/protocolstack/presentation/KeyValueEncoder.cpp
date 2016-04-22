/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "KeyValueEncoder.h"

#include <protocolstack/application/message/propertyNames.h>
#include <protocolstack/application/message/Printer.h>
#include <protocolstack/application/message/PrintFormat.h>

#include <sstream>
#include <functional>

namespace KeyValue
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
    output << value << "\n";
  }

  void writeValue(const std::string &value) override
  {
    output << value << "\n";
  }

  void writeKey(message::Property key) override
  {
    output << propertyName(key);
  }

  void writeKeyValueSeparator() override
  {
    output << " ";
  }

  void writeSeparator(bool) override
  {
  }

private:
  std::ostream &output;
  PropertyNameGetter propertyName{};

};

std::string encode(const message::Outgoing &message)
{
  std::stringstream stream;
  Format format{stream, message::propertyName};
  message::Printer printer{format};

  message.accept(printer);

  return stream.str();
}

}
