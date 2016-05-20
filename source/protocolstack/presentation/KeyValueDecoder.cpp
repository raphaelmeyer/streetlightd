/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "KeyValueDecoder.h"

#include <protocolstack/application/message/propertyNames.h>
#include <protocolstack/application/message/Property.h>

#include <sstream>
#include <list>

namespace presentation
{
namespace keyvalue
{

static std::string trim(const std::string &value)
{
  const auto start = value.find_first_not_of(' ');
  if (start == std::string::npos) {
    return {};
  }
  const auto end = value.find_last_not_of(' ');
  return value.substr(start, end+1);
}

static std::pair<std::string,std::string> split(const std::string line)
{
  const auto spacePos = line.find(' ');
  if (spacePos == std::string::npos) {
    return {};
  }
  const auto key = line.substr(0, spacePos);
  const auto value = trim(line.substr(spacePos));

  return {key, value};
}


class Parser
{
public:

  void init(const presentation::Message &message)
  {
    std::stringstream stream{message.asString()};
    std::string line;
    while (std::getline(stream, line, '\n')) {
      line = trim(line);
      if (!line.empty()) {
        lines.push_back(line);
      }
    }
  }

  message::Property parseProperty()
  {
    if (!hasMore()) {
      throw std::invalid_argument("no more data");
    }

    const auto line = lines.front();
    lines.pop_front();
    const auto value = split(line);

    currentData = value.second;

    auto key = value.first;
    if (key == message::propertyName(message::Property::Luminosity)) {
      return message::Property::Luminosity;
    }
    if (key == message::propertyName(message::Property::Warning)) {
      return message::Property::Warning;
    }
    throw std::invalid_argument("unknown property: " + key);
  }

  bool hasMore() const
  {
    return !lines.empty();
  }

  void parse(double &value)
  {
    try {
      std::size_t count = 0;
      value = std::stod(currentData, &count);
    } catch (std::invalid_argument) {
      throw std::invalid_argument("invalid double: " + currentData);
    }
  }

  void parse(std::string &value)
  {
    value = currentData;
  }

private:
  std::list<std::string> lines;
  std::string currentData;

};


class Decoder
{
public:

  void init(const presentation::Message &message)
  {
    parser.init(message);
  }

  message::Incoming decoded()
  {
    message::Incoming result{};

    while (parser.hasMore()) {
      auto property = parser.parseProperty();
      switch (property) {
      case message::Property::Luminosity:
        parseFor(result.luminosity);
        break;
      case message::Property::Warning:
        parseFor(result.warning);
        break;
      default:
        throw std::invalid_argument("unknown property: " + int(property));
        break;
      }
    }

    return result;
  }

private:
  Parser parser;

  template<typename T>
  void parseFor(message::Value<T> &value)
  {
    T raw;
    parser.parse(raw);
    value = raw;
  }
};

message::Incoming decode(const presentation::Message &message)
{
  Decoder decoder;
  decoder.init(message);
  return decoder.decoded();
}

}
}
