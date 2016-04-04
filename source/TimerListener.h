/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef TIMERLISTENER_H
#define TIMERLISTENER_H

class TimerListener
{
public:
  virtual ~TimerListener() = default;

  virtual void timeout() = 0;

};

#endif
