/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "JsonDecoder.h"

#include <jsoncpp/json/json.h>

namespace Json
{

Incoming::Message decode(const std::string &message)
{
  Json::Reader reader;
  Json::Value root;

  if (!reader.parse(message, root)) {
    throw std::invalid_argument("not valid json: " + message);
  }

  Incoming::Message result{};

  const auto &luminosity = root["luminosity"];
  if (!luminosity.isNull()) {
    result[Incoming::Type::Luminosity] = luminosity.asDouble();
  }

  return result;
}

}
