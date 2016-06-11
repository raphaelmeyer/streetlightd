/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "JsonParser.h"

#include <protocolstack/application/message/propertyNames.h>
#include <protocolstack/application/message/Property.h>

#include <list>

namespace presentation
{
namespace json
{

void Parser::reset(const Message &message)
{
  Json::Reader reader;

  if (!reader.parse(message.asString(), root)) {
    throw std::invalid_argument("not valid json: " + message.asString());
  }

  const auto mem = root.getMemberNames();
  members = std::list<std::string>{mem.cbegin(), mem.cend()};
}

message::Property Parser::parseProperty()
{
  if (!hasMore()) {
    throw std::invalid_argument("no more data");
  }

  auto key = members.front();
  members.pop_front();

  current = root[key];

  if (key == message::propertyName(message::Property::Luminosity)) {
    return message::Property::Luminosity;
  }
  if (key == message::propertyName(message::Property::Warning)) {
    return message::Property::Warning;
  }
  throw std::invalid_argument("unknown property: " + key);
}

bool Parser::hasMore() const
{
  return !members.empty();
}

void Parser::parse(double &value)
{
  value = current.asDouble();
}

void Parser::parse(std::string &value)
{
  value = current.asString();
}

}
}
