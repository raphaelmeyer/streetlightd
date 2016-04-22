/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "JsonEncoder.h"

#include <protocolstack/application/message/propertyNames.h>

#include <sstream>
#include <functional>

namespace Json
{

class Printer :
    public message::Visitor
{
public:
  typedef std::function<std::string(message::Property)> PropertyNameGetter;

  Printer(std::ostream &_output, PropertyNameGetter _propertyName) :
    output{_output},
    propertyName{_propertyName}
  {
  }

  void visit(message::Property property, const message::Value<double> &value) override
  {
    print(property, value);
  }

  void visit(message::Property property, const message::Value<std::string> &value) override
  {
    print(property, value);
  }

private:
  bool first{true};
  std::ostream &output;
  PropertyNameGetter propertyName{};

  void writeValue(double value)
  {
    output << value;
  }

  void writeValue(const std::string &value)
  {
    output << "\"" << value << "\"";
  }

  void writeKey(message::Property key)
  {
    output << "\"" + propertyName(key) + "\"";
  }

  void writeKeyValueSeparator()
  {
    output << ":";
  }

  void writeSeparator(bool first)
  {
    if (!first) {
      output << ",";
    }
  }

  template<typename T>
  void print(message::Property property, const message::Value<T> &value)
  {
    if (value.isValid()) {
      writeSeparator(first);
      first = false;
      writeKey(property);
      writeKeyValueSeparator();
      writeValue(value());
    }
  }

};

presentation::Message encode(const message::Outgoing &message)
{
  // A custom serilizer is written since the tested libraries do not
  // support custom float serializer.

  std::stringstream stream;
  Printer printer{stream, message::propertyName};

  stream << "{";
  message.accept(printer);
  stream << "}";

  return stream.str();
}

}
