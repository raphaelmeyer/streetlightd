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

std::string encode(const message::Outgoing &message)
{
  std::stringstream stream;

  if (message.brightness.isValid()) {
    stream << "brightness " << message.brightness() << std::endl;
  }

  return stream.str();
}

}
