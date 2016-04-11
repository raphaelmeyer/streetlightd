/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "KeyValueDecoder.h"

#include <sstream>

void KeyValueDecoder::setListener(KeyValueDecoder::Listener value)
{
  listener = value;
}

void KeyValueDecoder::decode(const std::string &message)
{
  std::stringstream stream{message};

  while (!stream.eof()) {
    std::string key;
    double value;

    stream >> key >> value;

    if (key == "luminosity") {
      listener(value);
    }
  }
}
