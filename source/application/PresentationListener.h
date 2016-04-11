/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef PRESENTATIONLISTENER_H
#define PRESENTATIONLISTENER_H

#include <application/IncomingMessage.h>

class PresentationListener
{
public:
  virtual ~PresentationListener() = default;

  virtual void received(const Incoming::Message &message) = 0;

};

#endif
