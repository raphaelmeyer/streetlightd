/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef INCOMINGMESSAGE_H
#define INCOMINGMESSAGE_H

#include <map>

namespace Incoming
{
  enum class Type
  {
    Luminosity
  };

  typedef std::map<Type, double> Message;
}

#endif
