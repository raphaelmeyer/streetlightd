/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef PROTOCOLSTACK_H
#define PROTOCOLSTACK_H

#include "application/ActiveApplication.h"
#include "presentation/Presentation.h"
#include "session/Session.h"

#include <memory>

class ProtocolStack
{
public:
  std::unique_ptr<Application> application;
  std::unique_ptr<Presentation> presentation;
  std::unique_ptr<Session> session;
};

#endif
