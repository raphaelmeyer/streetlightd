/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef NULLSESSION_H
#define NULLSESSION_H

#include "Session.h"

class NullSession :
    public Session
{
public:
  void send(const presentation::Message &) override;

  void setConfiguration(const SessionConfiguration &) override;
  void connect() override;
  void close() override;

  void setMessageCallback(Callback) override;

};

#endif
