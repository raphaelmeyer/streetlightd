/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef SESSION
#define SESSION

#include "Configuration.h"
#include "../presentation/Message.h"

#include <string>
#include <functional>

class Session
{
public:
  typedef std::function<void(const presentation::Message&)> Callback;

  virtual ~Session() = default;
  
  virtual void setConfiguration(const session::Configuration &value) = 0;

  virtual void connect() = 0;
  virtual void close() = 0;

  virtual void send(const presentation::Message &message) = 0;
  virtual void setMessageCallback(Callback function) = 0;

};

#endif
