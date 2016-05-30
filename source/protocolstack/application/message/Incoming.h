/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef MESSAGE_INCOMING_H
#define MESSAGE_INCOMING_H

#include "Value.h"
#include "Visitor.h"
#include "Message.h"

#include <ostream>

namespace message
{

  class Incoming :
      public Message
  {
  public:
    Value<double> luminosity{};
    Value<std::string> warning{};

    void accept(Visitor &visitor) const override;
  };

}

#endif
