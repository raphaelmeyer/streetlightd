/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "propertyNumbers.h"

#include <stdexcept>

namespace message
{

uint8_t propertyNumber(message::Property property)
{
  switch (property) {
  case message::Property::Brightness:     return 0;
  case message::Property::Moisture:       return 4;
  case message::Property::Proximity:      return 5;
  case message::Property::Info:           return 1;
  case message::Property::Luminosity:     return 2;
  case message::Property::Warning:        return 3;
  }
  throw std::invalid_argument("unknown property " + std::to_string(int(property)));
}

}
