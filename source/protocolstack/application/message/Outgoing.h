/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef MESSAGE_OUTGOING_H
#define MESSAGE_OUTGOING_H

#include "Value.h"

namespace message
{

  class Outgoing
  {
  public:
    Value<double> brightness{};
    Value<std::string> info{};

  };

}

#endif
