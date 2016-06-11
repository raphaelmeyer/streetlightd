/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef PRESENTATION_NULL_H
#define PRESENTATION_NULL_H

#include "Parser.h"
#include "PrintFormat.h"
#include "Message.h"

#include <protocolstack/application/message/Incoming.h>
#include <protocolstack/application/message/Outgoing.h>

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

class PrintFormat :
    public presentation::PrintFormat
{
public:
  void incomingHeader() override;
  void outgoingHeader() override;
  void footer() override;
  void value(bool, message::Property, double) override;
  void value(bool, message::Property, const std::string &) override;

  presentation::Message message() const override;

};

}

}

#endif
