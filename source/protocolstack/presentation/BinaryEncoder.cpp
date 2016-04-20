/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "BinaryEncoder.h"

#include "Binary.h"

#include <cmath>

namespace Binary
{

static void write(double value, std::vector<uint8_t> &data)
{
  data.push_back(uint8_t(std::round(value * 255)));
}

static void write(const std::string &value, std::vector<uint8_t> &data)
{
  data.push_back(value.size());
  data.insert(data.end(), value.begin(), value.end());
}

template<typename T>
static void writeIfValid(uint8_t key, const message::Value<T> &value, std::vector<uint8_t> &data)
{
  if (value.isValid()) {
    data.push_back(key);
    write(value(), data);
  }
}

presentation::Message encode(const message::Outgoing &message)
{
  std::vector<uint8_t> data{};
  writeIfValid(Brightness, message.brightness, data);
  writeIfValid(Info, message.info, data);
  return presentation::Message{data};
}

}
