/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "KeyValueDecoder.h"

#include <sstream>

namespace KeyValue
{

Incoming::Message decode(const std::string &message)
{
  Incoming::Message result{};

  std::stringstream stream{message};
  while (!stream.eof()) {
    std::string key;
    double value;

    stream >> key >> value;

    if (key == "luminosity") {
      result[Incoming::Type::Luminosity] = value;
    }
  }

  return result;
}

}
