/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "ActiveObject.h"

namespace concurrency
{

static void appRunner(Queue &queue)
{
  Queue::T call;
  while (queue.dequeue(call)) {
    call();
  }
}

ActiveObject::ActiveObject() :
  queue{},
  appThread{appRunner, std::ref(queue)}
{
}

ActiveObject::~ActiveObject()
{
  queue.close();
  appThread.join();
}

void ActiveObject::put(std::function<void ()> call)
{
  queue.enqueue(call);
}

}
