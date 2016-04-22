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

#include <ostream>

namespace message
{

  class Outgoing
  {
  public:

    Value<double> brightness{};
    Value<double> moisture{};
    Value<std::string> info{};

    void accept(Visitor &visitor) const;
  };

}

std::ostream &operator<<(std::ostream &stream, const message::Outgoing &message);

#endif
