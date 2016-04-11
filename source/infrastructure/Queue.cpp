/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Queue.h"

void Queue::enqueue(Queue::T call)
{
  std::lock_guard<std::mutex> lock{mutex};
  queue.push(call);

  condition.notify_one();
}

Queue::T Queue::dequeue()
{
  while (true) {
    std::unique_lock<std::mutex> lock{mutex};

    if (!queue.empty()) {
      const auto value = queue.front();
      queue.pop();
      return value;
    }

    condition.wait(lock);
  }
}
