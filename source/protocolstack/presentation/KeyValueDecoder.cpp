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

class Decoder
{
public:
  Decoder(const presentation::Message &message)
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

  message::Incoming decoded()
  {
    message::Incoming result{};

    while (hasMore()) {
      auto type = parseProperty();
      switch (type) {
      case message::Property::Luminosity:
        parseFor(result.luminosity);
        break;
      case message::Property::Warning:
        parseFor(result.warning);
        break;
      default:
        throw std::invalid_argument("unknown type: " + std::to_string(int(type)));
        break;
      }
    }

    return result;
  }

  message::Property parseProperty()
  {
    if (lines.empty()) {
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

  template<typename T>
  T parse();

  template<typename T>
  void parseFor(message::Value<T> &value)
  {
    value = parse<T>();
  }

  bool hasMore() const
  {
    return !lines.empty();
  }

private:
  std::list<std::string> lines;
  std::string currentData;

};

template<>
double Decoder::parse<double>()
{
  try {
    std::size_t count = 0;
    return std::stod(currentData, &count);
  } catch (std::invalid_argument) {
    throw std::invalid_argument("invalid double: " + currentData);
  }
}

template<>
std::string Decoder::parse<std::string>()
{
  return currentData;
}

message::Incoming decode(const presentation::Message &message)
{
  return Decoder{message}.decoded();
}

}
}
