/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef PRESENTATION_NULL_H
#define PRESENTATION_NULL_H

#include "Parser.h"

#include <protocolstack/application/message/Incoming.h>
#include <protocolstack/application/message/Outgoing.h>
#include <protocolstack/presentation/Message.h>

namespace presentation
{

namespace null
{

class Parser :
    public presentation::Parser
{
public:
  void reset(const presentation::Message &) override;

  message::Property parseProperty() override;

  bool hasMore() const override;

  void parse(double &) override;

  void parse(std::string &) override;

};

Message encode(const message::Outgoing &message);

}

}

#endif
