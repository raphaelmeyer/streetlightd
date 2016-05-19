/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef CLI_STREETLIGHTD_H
#define CLI_STREETLIGHTD_H

#include "Parser.h"

#include <protocolstack/StackFactory.h>
#include <protocolstack/session/Configuration.h>
#include <infrastructure/TimerConfiguration.h>

#include <Poco/Util/OptionSet.h>
#include <string>
#include <map>

namespace cli
{

class Configuration :
    public StackConfiguration,
    public session::Configuration,
    public TimerConfiguration
{
};

class Streetlightd
{
public:
  Streetlightd(Parser &parser);

  void addApplications(const std::set<std::string> &values);
  void addPresentations(const std::set<std::string> &values);
  void addSessions(const std::set<std::string> &values);

  Configuration parse(const std::vector<std::string> &arguments);

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

  Parser &parser;
  std::map<Layer, EnumEntry> enums;

  Poco::Util::OptionSet createOptions() const;
  std::string keyFor(Layer entry) const;
  EnumEntry entryFor(Layer entry) const;
  std::string valueFor(Layer type) const;
  std::map<Streetlightd::Layer, std::string> fillEnumValues() const;
  void fillStackConfig(StackConfiguration &config, std::map<Layer, std::string> enumValues) const;
  void fillSessionConfig(session::Configuration &config) const;
  void fillTimerConfig(TimerConfiguration &config) const;
};

}

#endif
