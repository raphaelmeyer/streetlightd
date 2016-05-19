/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef CLI_PARSER_DUMMY_H
#define CLI_PARSER_DUMMY_H

#include "../Parser.h"

namespace cli
{

class ParserDummy :
    public Parser
{
public:
  void parse(const std::vector<std::string> &arguments, const Poco::Util::OptionSet &options) override;
  Poco::Util::OptionSet parseOptions;

  void printHelp() const override;

  bool isValid() const override;

  std::string value(const std::string &key) const override;

  std::string value(const std::string &key, const std::string &def) const override;

  bool contains(const std::string &key) const override;

};

}

#endif
