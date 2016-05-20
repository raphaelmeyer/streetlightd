/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "BinaryDecoder.h"

#include <protocolstack/application/message/propertyNumbers.h>
#include <protocolstack/application/message/Property.h>

#include <algorithm>
#include <list>

namespace presentation
{
namespace binary
{

class Decoder
{
public:
  Decoder(const presentation::Message &message)
  {
    const auto values = message.asBinary();
    data = std::list<uint8_t>{values.cbegin(), values.cend()};
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
    if (data.empty()) {
      throw std::invalid_argument("no more data");
    }

    auto key = data.front();
    data.pop_front();
    if (key == message::propertyNumber(message::Property::Luminosity)) {
      return message::Property::Luminosity;
    }
    if (key == message::propertyNumber(message::Property::Warning)) {
      return message::Property::Warning;
    }
    throw std::invalid_argument("unknown property: " + std::to_string(key));
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
    return !data.empty();
  }


private:
  std::list<uint8_t> data;

};

template<>
double Decoder::parse<double>()
{
  if (data.empty()) {
    throw std::invalid_argument("expected 1 byte, got nothing");
  }


  const int8_t raw = static_cast<int8_t>(data.front());
  data.pop_front();

  return double(raw) / 100;
}

template<>
std::string Decoder::parse<std::string>()
{
  if (data.empty()) {
    throw std::invalid_argument("expected 1 byte, got nothing");
  }

  const uint8_t length = data.front();
  data.pop_front();

  if (data.size() < length) {
    throw std::invalid_argument("invalid length for string: " + std::to_string(length));
  }

  std::string text{};
  auto textEnd = data.begin();
  std::advance(textEnd, length);
  text.resize(length);
  std::transform(data.begin(), textEnd, text.begin(), [](uint8_t sym){return sym;});
  data.erase(data.begin(), textEnd);

  return text;
}


message::Incoming decode(const presentation::Message &message)
{
  return Decoder{message}.decoded();
}

}
}
