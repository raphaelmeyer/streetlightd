/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef SESSION
#define SESSION

#include <string>

class Session
{
public:
  virtual ~Session() = default;
  
  //TODO Following are method stubs, they may be altered to fit our needs
  
  virtual bool setUp() = 0;
  virtual bool connect() = 0;


  //TODO do not use a string (in the case somebody wants to send binary data)
  virtual void send(const std::string &message) = 0;
  virtual bool subscribe(std::string target) = 0;
  virtual bool close() = 0;

};

#endif
