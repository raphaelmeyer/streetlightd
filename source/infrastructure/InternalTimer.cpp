/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "InternalTimer.h"

static void runner(Timer::Callback *callback, bool *running)
{
  while (*running) {
    std::this_thread::sleep_for (std::chrono::seconds(1));
    (*callback)();
  }
}

InternalTimer::InternalTimer() :
  running{true},
  thread{runner, &callback, &running}
{
}

InternalTimer::~InternalTimer()
{
  running = false;
  thread.join();
}

void InternalTimer::setCallback(Timer::Callback value)
{
  callback = value;
}
