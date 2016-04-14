/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef MESSAGE_VALUE_H
#define MESSAGE_VALUE_H

#include <stdexcept>

namespace message
{

template<typename T>
class Value
{
public:
  Value(const T &_value) :
    value{_value},
    valid{true}
  {
  }

  Value() = default;

  bool isValid() const
  {
    return valid;
  }

  const T & operator()() const
  {
    if (!valid) {
      throw std::runtime_error("value not valid");
    }
    return value;
  }

  void operator=(const T &value)
  {
    this->value = value;
    valid = true;
  }

private:
  T value{};
  bool valid{false};
};

}

#endif
