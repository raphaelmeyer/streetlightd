/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include "TimerListener.h"
#include "PresentationListener.h"

class Application :
    public TimerListener,
    public PresentationListener
{
};

#endif
