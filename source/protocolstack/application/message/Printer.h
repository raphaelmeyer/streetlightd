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

#include <ostream>
#include <functional>

namespace message
{

class Printer :
    public Visitor
{
public:
  typedef std::function<std::string(Property)> PropertyNameGetter;

  Printer(std::ostream &output, PropertyNameGetter propertyName);

  void visit(Property property, const Value<double> &value) override;
  void visit(Property property, const Value<std::string> &value) override;

private:
  bool first{true};
  std::ostream &output;
  PropertyNameGetter propertyName{};

  std::string format(double value) const;
  std::string format(const std::string &value) const;
  std::string format(const std::string &key, const std::string &value) const;
  std::string nextSeparator();

  template<typename T>
  void print(Property property, const Value<T> &value)
  {
    if (value.isValid()) {
      output << nextSeparator();
      output << format(propertyName(property), format(value()));
    }
  }

};

}

#endif
