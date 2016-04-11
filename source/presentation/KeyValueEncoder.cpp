/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "KeyValueEncoder.h"

#include <sstream>

void KeyValueEncoder::setListener(KeyValueEncoder::Listener value)
{
  message = value;
}

void KeyValueEncoder::brightness(double value)
{
  std::stringstream stream;
  stream << "brightness " << value << std::endl;

  message(stream.str());
}

