/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef PRESENTATION_PARSER_H
#define PRESENTATION_PARSER_H

#include <protocolstack/presentation/Message.h>
#include <protocolstack/application/message/Property.h>

namespace presentation
{

class Parser
{
public:
  virtual ~Parser() = default;

  virtual void reset(const presentation::Message &message) = 0;

  virtual bool hasMore() const = 0;

  virtual message::Property parseProperty() = 0;
  virtual void parse(double &value) = 0;
  virtual void parse(std::string &value) = 0;

};

}

#endif
