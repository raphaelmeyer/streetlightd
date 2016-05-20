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

namespace presentation
{
namespace binary
{

template<typename T>
static T read(std::vector<uint8_t>::const_iterator &start, std::vector<uint8_t>::const_iterator &end);

template<>
double read<double>(std::vector<uint8_t>::const_iterator &start, std::vector<uint8_t>::const_iterator &end)
{
  if (start == end) {
    throw std::invalid_argument("expected 1 byte, got nothing");
  }

  const int8_t raw = static_cast<int8_t>(*start);
  start++;

  return double(raw) / 100;
}

template<>
std::string read<std::string>(std::vector<uint8_t>::const_iterator &start, std::vector<uint8_t>::const_iterator &end)
{
  if (start == end) {
    throw std::invalid_argument("expected 1 byte, got nothing");
  }

  const uint8_t length = *start;
  start++;

  if (std::distance(start, end) < length) {
    throw std::invalid_argument("invalid length for string: " + std::to_string(length));
  }

  std::string text{};
  const auto textEnd = start + length;
  text.resize(length);
  std::transform(start, textEnd, text.begin(), [](uint8_t sym){return sym;});
  start = textEnd;
  return text;
}

template<typename T>
static void write(message::Value<T> &value, std::vector<uint8_t>::const_iterator &start, std::vector<uint8_t>::const_iterator &end)
{
  value = read<T>(start, end);
}

template<typename T>
static void writeIfMatched(message::Property property, message::Value<T> &destination, uint8_t key, std::vector<uint8_t>::const_iterator &start, std::vector<uint8_t>::const_iterator &end)
{
  if (key == message::propertyNumber(property)) {
    write(destination, start, end);
  }
}

message::Incoming decode(const presentation::Message &message)
{
  const std::vector<uint8_t> data = message.asBinary();

  message::Incoming result{};

  auto start = data.begin();
  auto end = data.end();

  while (start != end) {
    const uint8_t key = *start;
    start++;
    const auto oldStart = start;

    writeIfMatched(message::Property::Luminosity, result.luminosity, key, start, end);
    writeIfMatched(message::Property::Warning, result.warning, key, start, end);

    if (start == oldStart) {
      throw std::invalid_argument("invalid key: " + std::to_string(key));
    }
  }

  return result;
}

}
}
