/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef CLI_COMMANDLINEPARSER_H
#define CLI_COMMANDLINEPARSER_H

#include <Poco/Util/OptionSet.h>
#include <ostream>
#include <string>
#include <vector>
#include <map>

namespace cli
{

class CommandLineParser
{
public:
  virtual void parse(const std::vector<std::string> &arguments, const Poco::Util::OptionSet &options) = 0;
  virtual void printHelp() const = 0;

  virtual bool isValid() const = 0;

  virtual std::string value(const std::string &key) const = 0;
  virtual std::string value(const std::string &key, const std::string &def) const = 0;
  virtual bool contains(const std::string &key) const = 0;
};


class CommandLineParserImplementation :
    public CommandLineParser
{
public:
  CommandLineParserImplementation(std::ostream &output);

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
