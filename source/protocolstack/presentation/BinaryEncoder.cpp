/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "BinaryEncoder.h"

#include <protocolstack/application/message/propertyNumbers.h>
#include <protocolstack/application/message/PrintFormat.h>
#include <protocolstack/application/message/Printer.h>

#include <cmath>

namespace presentation
{
namespace binary
{

class BinaryFormat :
    public message::PrintFormat
{
public:
  void incomingHeader() override
  {
    output.clear();
  }

  void outgoingHeader() override
  {
    incomingHeader();
  }

  void footer() override
  {
  }

  presentation::Message message() const
  {
    return output;
  }

  void writeValue(double value)
  {
    output.push_back(uint8_t(std::round(value * 100)));
  }

  void writeValue(const std::string &value)
  {
    output.push_back(value.size());
    output.insert(output.end(), value.begin(), value.end());
  }

  template<typename T>
  void write(message::Property property, const T &value)
  {
    output.push_back(message::propertyNumber(property));
    writeValue(value);
  }

  void value(bool, message::Property property, double value) override
  {
    write(property, value);
  }

  void value(bool, message::Property property, const std::string &value) override
  {
    write(property, value);
  }

private:
  std::vector<uint8_t> output;

};

presentation::Message encode(const message::Outgoing &message)
{
  BinaryFormat format{};
  message::Printer printer{format};

  message.accept(printer);

  return format.message();
}

}
}
