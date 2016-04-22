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

  virtual void visit(Property property, const Value<double> &value) = 0;
  virtual void visit(Property property, const Value<std::string> &value) = 0;

};

}

#endif
