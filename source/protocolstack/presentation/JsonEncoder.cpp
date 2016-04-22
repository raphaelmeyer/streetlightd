/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "JsonEncoder.h"

#include <sstream>

namespace Json
{

static void writeSeparator(std::ostream &stream, bool &first)
{
  if (first) {
    first = false;
  } else {
    stream << ",";
  }
}

static void add(std::ostream &stream, double value)
{
  stream << value;
}

static void add(std::ostream &stream, const std::string &value)
{
  stream << "\"" << value << "\"";
}

template<typename T>
static void addIfValid(std::ostream &stream, const std::string &name, const message::Value<T> &value, bool &first)
{
  if (value.isValid()) {
    writeSeparator(stream, first);
    stream << "\"" + name + "\":";
    add(stream, value());
  }
}

presentation::Message encode(const message::Outgoing &message)
{
  // A custom serilizer is written since the tested libraries do not
  // support custom float serializer.

  std::stringstream stream;

  stream << "{";

  bool first = true;

  addIfValid(stream, "brightness", message.brightness, first);
  addIfValid(stream, "moisture", message.moisture, first);
  addIfValid(stream, "info", message.info, first);

  stream << "}";

  return stream.str();
}

}
