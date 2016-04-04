/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef SESSIONLISTENER_H
#define SESSIONLISTENER_H

#include <string>

class SessionListener
{
public:
  virtual ~SessionListener() = default;

  //TODO do not use a string (in the case somebody wants to send binary data)
  virtual void decode(const std::string &) = 0;

};

#endif
