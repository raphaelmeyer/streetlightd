/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef SESSION_NULL_H
#define SESSION_NULL_H

#include "Session.h"

namespace session
{

class Null :
    public Session
{
public:
  void send(const presentation::Message &) override;

  void setConfiguration(const session::Configuration &) override;
  void connect() override;
  void close() override;

  void setMessageCallback(Callback) override;

};

}

#endif
