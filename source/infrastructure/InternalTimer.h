/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef INTERNALTIMER_H
#define INTERNALTIMER_H

#include "Timer.h"

#include <thread>

class InternalTimer :
    public Timer
{
public:
  InternalTimer();
  ~InternalTimer();

  void setCallback(Callback value) override;

private:
  Callback callback{};
  bool running;
  std::thread thread;

};

#endif
