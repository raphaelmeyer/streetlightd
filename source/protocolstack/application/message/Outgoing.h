/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef MESSAGE_OUTGOING_H
#define MESSAGE_OUTGOING_H

#include "Value.h"
#include "Visitor.h"
#include "Message.h"

#include <ostream>

namespace message
{

  class Outgoing :
      public Message
  {
  public:

    Value<double> brightness{};
    Value<double> moisture{};
    Value<double> proximity{};
    Value<std::string> info{};

    void accept(Visitor &visitor) const override;
  };

}

#endif
