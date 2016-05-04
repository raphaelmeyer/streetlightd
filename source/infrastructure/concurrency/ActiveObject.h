/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef CONCURRENCY_ACTIVEOBJECT_H
#define CONCURRENCY_ACTIVEOBJECT_H

#include "Queue.h"
#include <thread>

namespace concurrency
{

class ActiveObject
{
public:
  ActiveObject();
  ~ActiveObject();

  void put(std::function<void()> call);

private:
  Queue queue;
  std::thread appThread;

};

}

#endif
