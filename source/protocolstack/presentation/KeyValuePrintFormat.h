/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef PRESENTATION_KEYVALUE_PRINTFORMAT_H
#define PRESENTATION_KEYVALUE_PRINTFORMAT_H

#include "PrintFormat.h"
#include "Message.h"

#include <protocolstack/application/message/propertyNames.h>

#include <sstream>

namespace presentation
{
namespace keyvalue
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
  std::stringstream output;

  template<typename T>
  void write(message::Property property, const T &value)
  {
    output << message::propertyName(property) << " " << value << std::endl;
  }


};

}
}

#endif
