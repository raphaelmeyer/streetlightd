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
 * writeSeparator(true)  writeKey(name) writeKeyValueSeparator writeValue("quixli")
 * writeSeparator(false) writeKey(size) writeKeyValueSeparator writeValue(42)
 * writeSeparator(false) writeKey(id)   writeKeyValueSeparator writeValue(1337)
 * writeFooter();
 */
class PrintFormat
{
public:
  virtual ~PrintFormat() = default;

  virtual void writeIncomingHeader() = 0;
  virtual void writeOutgoingHeader() = 0;
  virtual void writeFooter() = 0;
  virtual void writeSeparator(bool first) = 0;
  virtual void writeKey(message::Property key) = 0;
  virtual void writeKeyValueSeparator() = 0;
  virtual void writeValue(double value) = 0;
  virtual void writeValue(const std::string &value) = 0;

};

}

#endif
