/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef INTERNALTIMER_H
#define INTERNALTIMER_H

#include "Timer.h"
#include "concurrency/Timer.h"

#include <memory>

class InternalTimer :
    public Timer
{
public:
  void setCallback(Callback value) override;

private:
  std::unique_ptr<concurrency::Timer> timer{nullptr};

};

#endif
