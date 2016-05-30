/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef MESSAGE_MESSAGE_H
#define MESSAGE_MESSAGE_H

#include "Visitor.h"

#include <ostream>

namespace message
{

  class Message
  {
  public:
    virtual void accept(Visitor &visitor) const = 0;
  };

}

std::ostream &operator<<(std::ostream &stream, const message::Message &message);


#endif
