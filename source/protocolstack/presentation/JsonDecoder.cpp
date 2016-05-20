/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "JsonDecoder.h"

#include <protocolstack/application/message/propertyNames.h>
#include <protocolstack/application/message/Property.h>

#include <jsoncpp/json/json.h>

namespace presentation
{
namespace json
{

static void write(message::Value<double> &value, const Json::Value &raw)
{
  value = raw.asDouble();
}

static void write(message::Value<std::string> &value, const Json::Value &raw)
{
  value = raw.asString();
}

template<typename T>
static void writeIfMatched(message::Property property, message::Value<T> &destination, const std::pair<std::string, Json::Value> &value)
{
  if (value.first == message::propertyName(property)) {
    write(destination, value.second);
  }
}

message::Incoming decode(const presentation::Message &message)
{
  Json::Reader reader;
  Json::Value root;

  if (!reader.parse(message.asString(), root)) {
    throw std::invalid_argument("not valid json: " + message.asString());
  }

  message::Incoming result{};

  for (const auto member : root.getMemberNames()) {
    std::pair<std::string, Json::Value> pair{member, root[member]};

    writeIfMatched(message::Property::Luminosity, result.luminosity, pair);
    writeIfMatched(message::Property::Warning, result.warning, pair);
  }

  return result;
}

}
}
