/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include <protocolstack/StackFactory.h>
#include <protocolstack/session/Configuration.h>
#include <infrastructure/TimerConfiguration.h>

#include <Poco/Util/OptionSet.h>
#include <ostream>
#include <vector>
#include <set>
#include <string>
#include <map>

class Configuration :
    public StackConfiguration,
    public session::Configuration,
    public TimerConfiguration
{
};

class CommandLineParser
{
public:
  CommandLineParser(std::ostream &output);

  void addApplications(const std::set<std::string> &values);
  void addPresentations(const std::set<std::string> &values);
  void addSessions(const std::set<std::string> &values);

  Configuration parse(const std::vector<std::string> &arguments) const;
private:
  class EnumEntry {
  public:
    std::string longName;
    std::string shortName;
    std::set<std::string> values;

    Poco::Util::Option asOption() const;
  };
  enum class Layer {
    Application,
    Presentation,
    Session
  };

  std::ostream &output;
  std::map<Layer, EnumEntry> enums;

  Poco::Util::OptionSet createOptions() const;
  void printHelp(const Poco::Util::OptionSet &options) const;
  std::string keyFor(Layer entry) const;
  EnumEntry entryFor(Layer entry) const;
  std::string valueFor(Layer type, const std::map<std::string, std::string> &values) const;
  std::map<CommandLineParser::Layer, std::string> fillEnumValues(const std::map<std::string, std::string> &values) const;
  std::map<std::string, std::string> parseToMap(const std::vector<std::string> &arguments, const Poco::Util::OptionSet &options) const;
  void fillStackConfig(StackConfiguration &config, std::map<Layer, std::string> enumValues) const;
  void fillSessionConfig(session::Configuration &config, std::map<std::string, std::string> values) const;
  void fillTimerConfig(TimerConfiguration &config, std::map<std::string, std::string> values) const;
};

#endif
