/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "ActiveObject.h"

static void appRunner(Queue *queue, bool *running)
{
  while (*running) {
    const auto call = queue->dequeue();
    call();
  }
}

ActiveObject::ActiveObject() :
  queue{},
  running{true},
  appThread{appRunner, &queue, &running}
{
}

ActiveObject::~ActiveObject()
{
  running = false;
  appThread.join();
}

void ActiveObject::put(std::function<void ()> call)
{
  queue.enqueue(call);
}
