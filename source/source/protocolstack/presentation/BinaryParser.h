/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef PRESENTATION_BINARY_PARSER_H
#define PRESENTATION_BINARY_PARSER_H

#include "Parser.h"

#include <protocolstack/application/message/Incoming.h>
#include <protocolstack/presentation/Message.h>

#include <list>

namespace presentation
{
namespace binary
{

class Parser :
    public presentation::Parser
{
public:
  void reset(const presentation::Message &message) override;

  message::Property parseProperty() override;

  bool hasMore() const override;

  void parse(double &value) override;

  void parse(std::string &value) override;

private:
  std::list<uint8_t> data;

};

}
}

#endif
