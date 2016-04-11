/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef ACTIVEOBJECT_H
#define ACTIVEOBJECT_H

#include "Queue.h"
#include <thread>

class ActiveObject
{
public:
  ActiveObject();
  ~ActiveObject();

  void put(std::function<void()> call);

private:
  Queue queue;
  bool running;
  std::thread appThread;

};

#endif
