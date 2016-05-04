/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Timer.h"

namespace concurrency
{

static void runner(Timer::Callback callback, bool &running, std::mutex &mutex, std::condition_variable &signal)
{
  while (true) {
    {
      std::unique_lock<std::mutex> lock{mutex};

      const bool timeout = signal.wait_for(lock, std::chrono::seconds(1), [&running]{
        return !running;
      });

      if (timeout) {
        return;
      }
    }

    callback();
  }
}

Timer::Timer(Timer::Callback callback) :
  running{true},
  thread{runner, callback, std::ref(running), std::ref(mutex), std::ref(signal)}
{
}

Timer::~Timer()
{
  {
    std::lock_guard<std::mutex> lock{mutex};
    running = false;
  }
  signal.notify_one();
  thread.join();
}

}
