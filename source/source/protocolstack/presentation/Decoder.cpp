/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Decoder.h"

namespace presentation
{

template<typename T>
void parseFor(message::Value<T> &value, Parser &parser)
{
  T raw;
  parser.parse(raw);
  value = raw;
}

message::Incoming decode(Parser &parser)
{
  message::Incoming result{};

  while (parser.hasMore()) {
    auto property = parser.parseProperty();
    switch (property) {
    case message::Property::Luminosity:
      parseFor(result.luminosity, parser);
      break;
    case message::Property::Warning:
      parseFor(result.warning, parser);
      break;
    default:
      throw std::invalid_argument("unknown property: " + int(property));
      break;
    }
  }

  return result;
}


}
