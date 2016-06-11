/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef MESSAGE_PRINTER_H
#define MESSAGE_PRINTER_H

#include "Value.h"
#include "Visitor.h"
#include "PrintFormat.h"

#include <ostream>
#include <functional>

namespace message
{

class Printer :
    public Visitor
{
public:
  typedef std::function<std::string(Property)> PropertyNameGetter;

  Printer(PrintFormat &format);

  void incomingHeader() override;
  void incomingFooter() override;
  void outgoingHeader() override;
  void outgoingFooter() override;
  void property(Property property, const Value<double> &value) override;
  void property(Property property, const Value<std::string> &value) override;

private:
  bool first{true};
  PrintFormat &format;

  template<typename T>
  void write(Property property, const Value<T> &value)
  {
    if (value.isValid()) {
      format.value(first, property, value());
      first = false;
    }
  }

};

}

#endif
