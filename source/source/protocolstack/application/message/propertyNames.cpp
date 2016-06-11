/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "propertyNames.h"

#include <stdexcept>

namespace message
{

std::string propertyName(Property property)
{
  switch (property) {
  case Property::Brightness:
    return "brightness";
  case Property::Moisture:
    return "moisture";
  case Property::Proximity:
    return "proximity";
  case Property::Info:
    return "info";
  case Property::Luminosity:
    return "luminosity";
  case Property::Warning:
    return "warning";
  }
  throw std::invalid_argument("unknown property " + std::to_string(int(property)));
}

}
