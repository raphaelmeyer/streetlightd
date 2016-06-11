/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef PRESENTATION_BINARY_PRINTFORMAT_H
#define PRESENTATION_BINARY_PRINTFORMAT_H

#include "PrintFormat.h"
#include "Message.h"

#include <protocolstack/application/message/propertyNumbers.h>

namespace presentation
{
namespace binary
{

class PrintFormat :
    public presentation::PrintFormat
{
public:
  void incomingHeader() override;
  void outgoingHeader() override;
  void footer() override;
  void value(bool, message::Property property, double value) override;
  void value(bool, message::Property property, const std::string &value) override;

  presentation::Message message() const override;

private:
  std::vector<uint8_t> output;

  void writeValue(double value);
  void writeValue(const std::string &value);

  template<typename T>
  void write(message::Property property, const T &value)
  {
    output.push_back(message::propertyNumber(property));
    writeValue(value);
  }

};

}
}

#endif
