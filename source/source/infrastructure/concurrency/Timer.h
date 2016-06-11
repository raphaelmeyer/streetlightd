/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef CONCURRENCY_TIMER_H
#define CONCURRENCY_TIMER_H

#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>

namespace concurrency
{

class Timer final
{
public:
  typedef std::function<void()> Callback;

  Timer(Callback callback);
  ~Timer();

private:
  std::mutex mutex{};
  std::condition_variable signal{};
  bool running{true};
  std::thread thread;

};

}

#endif
