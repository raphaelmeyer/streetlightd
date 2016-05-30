/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "JsonEncoder.h"

#include <protocolstack/application/message/propertyNames.h>
#include <protocolstack/application/message/PrintFormat.h>
#include <protocolstack/application/message/Printer.h>

#include <sstream>
#include <functional>

namespace presentation
{
namespace json
{

class JsonFormat :
    public message::PrintFormat
{
public:
  void incomingHeader() override
  {
    output.clear();
    output << "{";
  }

  void outgoingHeader() override
  {
    incomingHeader();
  }

  void footer() override
  {
    output << "}";
  }

  presentation::Message message() const
  {
    return output.str();
  }

  void writeValue(double value)
  {
    output << value;
  }

  void writeValue(const std::string &value)
  {
    output << "\"" << value << "\"";
  }

  void separator(bool first)
  {
    if (!first) {
      output << ",";
    }
  }

  template<typename T>
  void write(bool first, message::Property property, const T &value)
  {
    separator(first);
    output << "\"" + message::propertyName(property) + "\"";
    output << ":";
    writeValue(value);
  }

  void value(bool first, message::Property property, double value) override
  {
    write(first, property, value);
  }

  void value(bool first, message::Property property, const std::string &value) override
  {
    write(first, property, value);
  }

private:
  std::stringstream output;

};

presentation::Message encode(const message::Outgoing &message)
{
  // A custom serializer is written since the tested libraries do not
  // support custom float serializer.

  JsonFormat format{};
  message::Printer printer{format};

  message.accept(printer);

  return format.message();
}

}
}
