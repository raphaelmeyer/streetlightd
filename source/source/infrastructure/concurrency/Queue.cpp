/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Queue.h"

namespace concurrency
{

void Queue::enqueue(Queue::T call)
{
  {
    std::lock_guard<std::mutex> lock{mutex};
    queue.push(call);
  }
  notEmpty.notify_one();
}

bool Queue::dequeue(T &call)
{
  std::unique_lock<std::mutex> lock{mutex};

  notEmpty.wait(lock, [&]{
    return !queue.empty() || finished;
  });

  if (!queue.empty()) {
    call = queue.front();
    queue.pop();
    return true;
  }

  return false;
}

void Queue::close()
{
  {
    std::lock_guard<std::mutex> lock{mutex};
    finished = true;
  }
  notEmpty.notify_one();
}

}
