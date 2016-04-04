/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef ACTOR_H
#define ACTOR_H

class Actor
{
public:
  virtual ~Actor() = default;

  virtual void set(double) = 0;

};

#endif
