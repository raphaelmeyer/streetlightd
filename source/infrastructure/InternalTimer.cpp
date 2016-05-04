/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "InternalTimer.h"

static void runner(Timer::Callback &callback, bool &running, std::mutex &mutex)
{
  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));

    Timer::Callback cb;
    {
      std::lock_guard<std::mutex> lock{mutex};
      if (!running) {
        return;
      }
      cb = callback;
    }
    cb();
  }
}

InternalTimer::InternalTimer() :
  running{true},
  thread{runner, std::ref(callback), std::ref(running), std::ref(mutex)}
{
}

InternalTimer::~InternalTimer()
{
  {
    std::lock_guard<std::mutex> lock{mutex};
    running = false;
  }
  thread.join();
}

void InternalTimer::setCallback(Timer::Callback value)
{
  {
    std::lock_guard<std::mutex> lock{mutex};
    callback = value;
  }
}
