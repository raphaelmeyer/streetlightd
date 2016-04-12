/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include <Poco/Util/OptionSet.h>
#include <ostream>
#include <vector>
#include <set>
#include <string>

class Configuration
{
public:
  std::string application{};
  std::string presentation{};
  std::string session{};

  operator bool() const;
};

class CommandLineParser
{
public:
  CommandLineParser(std::ostream &output);

  void addApplications(const std::set<std::string> &values);
  void addPresentations(const std::set<std::string> &values);
  void addSessions(const std::set<std::string> &values);

  Configuration parse(const std::vector<std::string> &arguments);

private:
  std::ostream &output;
  std::set<std::string> application{};
  std::set<std::string> presentation{};
  std::set<std::string> session{};

  void printHelp(const Poco::Util::OptionSet &options);

};

#endif
