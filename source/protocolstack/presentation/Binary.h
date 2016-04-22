/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef BINARY_H
#define BINARY_H

#include <protocolstack/application/message/Property.h>

namespace Binary
{

static const uint8_t Brightness{0};
static const uint8_t Info{1};
static const uint8_t Moisture{4};
static const uint8_t Luminosity{2};
static const uint8_t Warning{3};

static uint8_t propertyNumber(message::Property property)
{
  switch (property) {
  case message::Property::Brightness:
    return Brightness;
  case message::Property::Moisture:
    return Moisture;
  case message::Property::Info:
    return Info;
  case message::Property::Luminosity:
    return Luminosity;
  case message::Property::Warning:
    return Warning;
  }
  throw std::invalid_argument("unknown property " + std::to_string(int(property)));
}

}

#endif
