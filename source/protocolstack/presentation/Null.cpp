/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Null.h"

namespace presentation
{

namespace null
{

message::Incoming decode(const Message &)
{
  return {};
}

Message encode(const message::Outgoing &)
{
  return {};
}

}

}
