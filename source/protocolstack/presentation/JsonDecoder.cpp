/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "JsonDecoder.h"
#include "Decoder.h"

#include <protocolstack/application/message/propertyNames.h>
#include <protocolstack/application/message/Property.h>

#include <jsoncpp/json/json.h>

#include <list>

namespace presentation
{
namespace json
{

class Parser :
    public presentation::Parser
{
public:
  Parser(const presentation::Message &message)
  {
    Json::Reader reader;

    if (!reader.parse(message.asString(), root)) {
      throw std::invalid_argument("not valid json: " + message.asString());
    }

    const auto mem = root.getMemberNames();
    members = std::list<std::string>{mem.cbegin(), mem.cend()};
  }

  message::Property parseProperty() override
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

  bool hasMore() const override
  {
    return !members.empty();
  }

  void parse(double &value) override
  {
    value = current.asDouble();
  }

  void parse(std::string &value) override
  {
    value = current.asString();
  }

private:
  std::list<std::string> members;
  Json::Value current;
  Json::Value root;

};

message::Incoming decode(const presentation::Message &message)
{
  Parser parser{message};
  return decode(parser);
}

}
}
