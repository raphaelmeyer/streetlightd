/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "format.h"

std::string std::to_string(const std::string &value)
{
  return value;
}

std::ostream &operator <<(std::ostream &stream, const std::vector<std::string> &values)
{
  bool first = true;
  for (const auto &value : values) {
    if (first) {
      first = false;
    } else {
      stream << " ";
    }
    stream << value;
  }
  return stream;
}
