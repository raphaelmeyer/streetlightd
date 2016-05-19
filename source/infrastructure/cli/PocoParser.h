/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef CLI_POCOPARSER_H
#define CLI_POCOPARSER_H

#include "Parser.h"

#include <Poco/Util/OptionSet.h>
#include <ostream>
#include <string>
#include <vector>
#include <map>

namespace cli
{

class PocoParser :
    public Parser
{
public:
  PocoParser(std::ostream &output);

  void parse(const std::vector<std::string> &arguments, const Poco::Util::OptionSet &options) override;
  void printHelp() const override;

  bool isValid() const override;

  std::string value(const std::string &key) const override;
  std::string value(const std::string &key, const std::string &def) const override;
  bool contains(const std::string &key) const override;

private:
  Poco::Util::OptionSet options;
  std::ostream &output;
  bool valid{false};
  std::map<std::string, std::string> map;

};

}

#endif
