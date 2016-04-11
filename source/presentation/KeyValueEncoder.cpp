/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "KeyValueEncoder.h"

#include <sstream>

namespace KeyValue
{

std::string encode(double brightness)
{
  std::stringstream stream;
  stream << "brightness " << brightness << std::endl;

  return stream.str();
}

}
