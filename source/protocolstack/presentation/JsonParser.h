/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef PRESENTATION_JSON_PARSER_H
#define PRESENTATION_JSON_PARSER_H

#include "Parser.h"

#include <protocolstack/application/message/Incoming.h>
#include <protocolstack/presentation/Message.h>

#include <jsoncpp/json/json.h>
#include <list>

namespace presentation
{
namespace json
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
  std::list<std::string> members;
  Json::Value current;
  Json::Value root;

};

}
}

#endif
