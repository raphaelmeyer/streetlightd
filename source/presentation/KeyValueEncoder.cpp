/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "KeyValueEncoder.h"

#include <sstream>

KeyValueEncoder::KeyValueEncoder(Session &_session) :
  session{_session}
{
}

void KeyValueEncoder::brightness(double value)
{
  std::stringstream stream;
  stream << "brightness " << value << std::endl;

  session.send(stream.str());
}

