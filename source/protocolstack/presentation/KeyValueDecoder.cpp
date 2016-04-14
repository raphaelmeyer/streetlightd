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

  std::string line;
  while (std::getline(stream, line, '\n')) {
    auto spacePos = line.find(' ');
    auto key = line.substr(0, spacePos);
    auto value = line.substr(spacePos+1);
    if (key == "luminosity") {
      try {
        std::size_t count = 0;
        double parsed  = std::stod(value, &count);
        result.luminosity = parsed;
      } catch (std::invalid_argument) {
      }
    }
  }

  return result;
}

}
