/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "KeyValueEncoder.h"

#include <protocolstack/application/message/propertyNames.h>
#include <protocolstack/application/message/PrintFormat.h>
#include <protocolstack/application/message/Printer.h>

#include <sstream>
#include <functional>

namespace presentation
{
namespace keyvalue
{

class KeyValueFormat :
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
    return output.str();
  }

  template<typename T>
  void write(message::Property property, const T &value)
  {
    output << message::propertyName(property) << " " << value << std::endl;
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
  std::stringstream output;

};

Message encode(const message::Outgoing &message)
{
  KeyValueFormat format{};
  message::Printer printer{format};

  message.accept(printer);

  return format.message();
}

}
}
