/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "KeyValueEncoder.h"

#include <sstream>

namespace KeyValue
{

template<typename T>
static void addIfValid(std::ostream &stream, const std::string &name, const message::Value<T> &value)
{
  if (value.isValid()) {
    stream << name << " " << value() << std::endl;
  }
}

std::string encode(const message::Outgoing &message)
{
  std::stringstream stream;

  addIfValid(stream, "brightness", message.brightness);
  addIfValid(stream, "moisture", message.moisture);
  addIfValid(stream, "info", message.info);

  return stream.str();
}

}
