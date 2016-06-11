/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "InternalTimer.h"

void InternalTimer::setCallback(Timer::Callback value)
{
  timer = std::unique_ptr<concurrency::Timer>(new concurrency::Timer(value));
}
