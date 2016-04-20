/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef MESSAGE_INCOMING_H
#define MESSAGE_INCOMING_H

#include "Value.h"
#include <ostream>

namespace message
{

  class Incoming
  {
  public:
    Value<double> luminosity{};
    Value<std::string> warning{};

  };

}

std::ostream &operator<<(std::ostream &stream, const message::Incoming &message);


#endif
