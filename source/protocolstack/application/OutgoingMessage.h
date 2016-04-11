/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef OUTGOINGMESSAGE_H
#define OUTGOINGMESSAGE_H

#include <map>

namespace Outgoing
{
  enum class Type
  {
    Brightness
  };

  typedef std::map<Type, double> Message;
}

#endif
