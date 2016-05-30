/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "BinaryEncoder.h"

#include <protocolstack/application/message/propertyNumbers.h>
#include <protocolstack/application/message/Printer.h>
#include <protocolstack/application/message/PrintFormat.h>

#include <cmath>

namespace presentation
{
namespace binary
{

class Format :
    public message::PrintFormat
{
public:
  void writeIncomingHeader() override
  {
    output.clear();
  }

  void writeOutgoingHeader() override
  {
    writeIncomingHeader();
  }

  void writeFooter() override
  {
  }

  presentation::Message message() const
  {
    return output;
  }

  void writeValue(double value) override
  {
    output.push_back(uint8_t(std::round(value * 100)));
  }

  void writeValue(const std::string &value) override
  {
    output.push_back(value.size());
    output.insert(output.end(), value.begin(), value.end());
  }

  void writeKey(message::Property key) override
  {
    output.push_back(message::propertyNumber(key));
  }

  void writeKeyValueSeparator() override
  {
  }

  void writeSeparator(bool) override
  {
  }

private:
  std::vector<uint8_t> output;

};

presentation::Message encode(const message::Outgoing &message)
{
  Format format{};
  message::Printer printer{format};

  message.accept(printer);

  return format.message();
}

}
}
