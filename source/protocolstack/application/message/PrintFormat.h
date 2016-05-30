/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef MESSAGE_PRINTFORMAT_H
#define MESSAGE_PRINTFORMAT_H

#include "Property.h"

#include <string>

namespace message
{

/**
 * Used to serialize a message into a varity of formats.
 *
 * For the message:
 *   name = "quixli"
 *   size = 42
 *   id = 1337
 *
 * The methods are called:
 *
 * write*Header();
 * writeValue(true, name, "quixli")
 * writeValue(false, size, 42)
 * writeValue(false, id, 1337)
 * writeFooter();
 */
class PrintFormat
{
public:
  virtual ~PrintFormat() = default;

  virtual void incomingHeader() = 0;
  virtual void outgoingHeader() = 0;
  virtual void footer() = 0;
  virtual void value(bool first, message::Property property, double value) = 0;
  virtual void value(bool first, message::Property property, const std::string &value) = 0;

};

}

#endif
