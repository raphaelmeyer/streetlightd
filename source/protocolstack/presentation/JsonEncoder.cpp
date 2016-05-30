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

namespace presentation
{
namespace json
{

class Format :
    public message::PrintFormat
{
public:
  void writeIncomingHeader() override
  {
    output.clear();
    output << "{";
  }

  void writeOutgoingHeader() override
  {
    writeIncomingHeader();
  }

  void writeFooter() override
  {
    output << "}";
  }

  presentation::Message message() const
  {
    return output.str();
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
    output << "\"" + message::propertyName(key) + "\"";
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
  std::stringstream output;

};

presentation::Message encode(const message::Outgoing &message)
{
  // A custom serializer is written since the tested libraries do not
  // support custom float serializer.

  Format format{};
  message::Printer printer{format};

  message.accept(printer);

  return format.message();
}

}
}
