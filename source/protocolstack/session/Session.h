/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef SESSION
#define SESSION

#include "SessionConfiguration.h"

#include <string>
#include <functional>

class Session
{
public:
  typedef std::function<void(const std::string&)> Callback;

  virtual ~Session() = default;
  
  virtual void setConfiguration(const SessionConfiguration &value) = 0;

  virtual void connect() = 0;
  virtual void close() = 0;

  //TODO do not use a string (in the case somebody wants to send binary data)
  virtual void send(const std::string &message) = 0;
  virtual void setMessageCallback(Callback function) = 0;

};

#endif
