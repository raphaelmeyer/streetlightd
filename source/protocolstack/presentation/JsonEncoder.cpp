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

std::string encode(const message::Outgoing &message)
{
  // A custom serilizer is written since the tested libraries do not
  // support custom float serializer.

  std::stringstream stream;

  stream << "{";

  if (message.brightness.isValid()) {
    stream << "\"brightness\":" << message.brightness();
  }
  //TODO use nicer solution
  if (message.brightness.isValid() && message.info.isValid()) {
    stream << ",";
  }
  if (message.info.isValid()) {
    stream << "\"info\":\"" << message.info() << "\"";
  }

  stream << "}";

  return stream.str();
}

}
