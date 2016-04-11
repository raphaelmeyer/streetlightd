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

std::string encode(const Outgoing::Message &message)
{
  std::stringstream stream;

  const auto &brightness = message.find(Outgoing::Type::Brightness);
  if (brightness != message.end()) {
    stream << "brightness " << brightness->second << std::endl;
  }

  return stream.str();
}

}
