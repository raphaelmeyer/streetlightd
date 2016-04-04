/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include "TimerListener.h"
#include "Brightness.h"
#include "Presentation.h"

/**
 * Simple application logic that reads all values on a timeout and forwards it.
 * Same for receiving.
 */
class Application :
    public TimerListener
{
public:
  Application(Brightness &brightness, Presentation &presentation);

  void timeout() override;

private:
  Brightness &brightness_;
  Presentation &presentation;

};

#endif
