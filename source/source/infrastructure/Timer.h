/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef TIMER_H
#define TIMER_H

#include <functional>

class Timer
{
public:
  typedef std::function<void()> Callback;

  virtual ~Timer() = default;

  virtual void setCallback(Callback value) = 0;

};

#endif
