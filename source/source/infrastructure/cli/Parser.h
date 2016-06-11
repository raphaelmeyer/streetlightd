/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef CLI_PARSER_H
#define CLI_PARSER_H

#include <Poco/Util/OptionSet.h>
#include <string>
#include <vector>

namespace cli
{

class Parser
{
public:
  virtual ~Parser() = default;

  virtual void parse(const std::vector<std::string> &arguments, const Poco::Util::OptionSet &options) = 0;
  virtual void printHelp() const = 0;

  virtual bool isValid() const = 0;

  virtual std::string value(const std::string &key) const = 0;
  virtual std::string value(const std::string &key, const std::string &def) const = 0;
  virtual bool contains(const std::string &key) const = 0;
};

}

#endif
