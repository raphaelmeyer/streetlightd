/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef MESSAGE_FORMAT_H
#define MESSAGE_FORMAT_H

#include "Value.h"

#include <string>
#include <vector>
#include <ostream>

namespace std
{

string to_string(const string &value);

}

namespace message
{

template<typename T>
static std::string formatValue(const std::string &name, const message::Value<T> &value)
{
  if (value.isValid()) {
    return name + "=\"" + std::to_string(value()) + "\"";
  } else {
    return {};
  }
}

template<typename T>
static void addIfValid(std::vector<std::string> &values, const std::string &name, const message::Value<T> &value)
{
  const auto text = formatValue(name, value);
  if (!text.empty()) {
    values.push_back(text);
  }
}

}

std::ostream &operator <<(std::ostream &stream, const std::vector<std::string> &values);


#endif
