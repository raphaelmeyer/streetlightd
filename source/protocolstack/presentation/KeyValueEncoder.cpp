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

namespace presentation
{
namespace keyvalue
{

class Format :
    public message::PrintFormat
{
public:
  void header()
  {
    output.clear();
  }

  void footer()
  {
  }

  presentation::Message message() const
  {
    return output.str();
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
    output << message::propertyName(key);
  }

  void writeKeyValueSeparator() override
  {
    output << " ";
  }

  void writeSeparator(bool) override
  {
  }

private:
  std::stringstream output;

};

Message encode(const message::Outgoing &message)
{
  Format format{};
  message::Printer printer{format};

  format.header();
  message.accept(printer);
  format.footer();

  return format.message();
}

}
}
