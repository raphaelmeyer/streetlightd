/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "KeyValueDecoder.h"

#include <sstream>

namespace KeyValue
{

static std::string trim(const std::string &value)
{
  const auto start = value.find_first_not_of(' ');
  if (start == std::string::npos) {
    return {};
  }
  const auto end = value.find_last_not_of(' ');
  return value.substr(start, end);
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

static void write(message::Value<double> &value, const std::string &raw)
{
  try {
    std::size_t count = 0;
    double parsed  = std::stod(raw, &count);
    value = parsed;
  } catch (std::invalid_argument) {
  }
}

static void write(message::Value<std::string> &value, const std::string &raw)
{
  value = raw;
}

template<typename T>
static void writeIfMatched(const std::string &name, message::Value<T> &destination, const std::pair<std::string,std::string> &value)
{
  if (value.first == name) {
    write(destination, value.second);
  }
}

message::Incoming decode(const presentation::Message &message)
{
  message::Incoming result{};

  std::stringstream stream{message.asString()};

  std::string line;
  while (std::getline(stream, line, '\n')) {
    const auto value = split(line);

    writeIfMatched("luminosity", result.luminosity, value);
    writeIfMatched("warning", result.warning, value);
  }

  return result;
}

}
