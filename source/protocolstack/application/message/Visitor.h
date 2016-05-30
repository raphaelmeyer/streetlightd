/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef MESSAGE_VISITOR_H
#define MESSAGE_VISITOR_H

#include "Value.h"
#include "Property.h"

namespace message
{

class Visitor
{
public:
  virtual ~Visitor() = default;

  virtual void incomingHeader() = 0;
  virtual void outgoingHeader() = 0;
  virtual void incomingFooter() = 0;
  virtual void outgoingFooter() = 0;
  virtual void property(Property property, const Value<double> &value) = 0;
  virtual void property(Property property, const Value<std::string> &value) = 0;

};

}

#endif
