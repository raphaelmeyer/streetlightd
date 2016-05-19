/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Streetlightd.h"

#include <map>

namespace cli
{

static const std::string HOST_ARGUMENT = "host";
static const std::string USER_ARGUMENT = "user";
static const std::string PASSWORD_ARGUMENT = "password";
static const std::string TIMER_ARGUMENT = "external-timer";

Streetlightd::Streetlightd(Parser &_parser) :
  parser{_parser}
{
  enums[Layer::Application] = EnumOption{"application", "a", {}};
  enums[Layer::Presentation] = EnumOption{"presentation", "p", {}};
  enums[Layer::Session] = EnumOption{"session", "s", {}};
}

void Streetlightd::addApplications(const std::set<std::string> &values)
{
  enums[Layer::Application].values.insert(values.begin(), values.end());
}

void Streetlightd::addPresentations(const std::set<std::string> &values)
{
  enums[Layer::Presentation].values.insert(values.begin(), values.end());
}

void Streetlightd::addSessions(const std::set<std::string> &values)
{
  enums[Layer::Session].values.insert(values.begin(), values.end());
}

Configuration Streetlightd::parse(const std::vector<std::string> &arguments)
{
  parser.parse(arguments, createOptions());
  if (!parser.isValid()) {
    parser.printHelp();
    return {};
  }

  if (parser.contains("help")) {
    parser.printHelp();
    return {};
  }

  auto enumValues = fillEnumValues();
  if (enumValues.empty()) {
    //TODO test this case
    parser.printHelp();
    return {};
  }

  Configuration config{};
  fillStackConfig(config, enumValues);
  fillSessionConfig(config);
  fillTimerConfig(config);
  return config;
}

std::map<Streetlightd::Layer,std::string> Streetlightd::fillEnumValues() const
{
  std::map<Layer,std::string> enumValues{};
  for (const auto layer : {Layer::Application, Layer::Presentation, Layer::Session}) {
    const auto value = valueFor(layer);
    if (value.empty()) {
      return {};
    }
    enumValues[layer] = value;
  }

  return enumValues;
}

void Streetlightd::fillStackConfig(StackConfiguration &config, std::map<Layer, std::string> enumValues) const
{
  config.application = enumValues[Layer::Application];
  config.presentation = enumValues[Layer::Presentation];
  config.session = enumValues[Layer::Session];
}

void Streetlightd::fillSessionConfig(session::Configuration &config) const
{
  config.host = parser.value(HOST_ARGUMENT, "");
  config.user = parser.value(USER_ARGUMENT, "");
  config.password = parser.value(PASSWORD_ARGUMENT, "");
}

void Streetlightd::fillTimerConfig(TimerConfiguration &config) const
{
  config.externalTimer = parser.contains(TIMER_ARGUMENT);
}

Poco::Util::OptionSet Streetlightd::createOptions() const
{
  Poco::Util::OptionSet options{};

  options.addOption(Poco::Util::Option{"help",         "h", "print this help", false});

  for (const auto &opt : enums) {
    options.addOption(opt.second.asOption());
  }

  options.addOption(Poco::Util::Option{HOST_ARGUMENT,     "", "host to connect to\nfor azure-* sessions, this is <iot hub name>.azure-devices.net", false}.argument("<" + HOST_ARGUMENT + ">"));
  options.addOption(Poco::Util::Option{USER_ARGUMENT,     "", "username for the session\nfor azure-* sessions, this is the device name", false}.argument("<" + USER_ARGUMENT + ">"));
  options.addOption(Poco::Util::Option{PASSWORD_ARGUMENT, "", "password for the session\nfor azure-* sessions, this is the key", false}.argument("<" + PASSWORD_ARGUMENT + ">"));
  options.addOption(Poco::Util::Option{TIMER_ARGUMENT,    "", "trigger updates via DBus", false});
  return options;
}

std::string Streetlightd::keyFor(Streetlightd::Layer entry) const
{
  const auto &pos = enums.find(entry);
  if (pos == enums.end()) {
    throw std::runtime_error("entry not defined: " + std::to_string(int(entry)));
  }
  return pos->second.longName;
}

EnumOption Streetlightd::entryFor(Streetlightd::Layer entry) const
{
  const auto &pos = enums.find(entry);
  if (pos == enums.end()) {
    throw std::runtime_error("entry not defined: " + std::to_string(int(entry)));
  }
  return pos->second;
}

std::string Streetlightd::valueFor(Streetlightd::Layer type) const
{
  EnumOption entry = entryFor(type);
  if (!parser.contains(entry.longName)) {
    return {};
  }

  const auto value = parser.value(entry.longName);
  const auto contains = entry.values.find(value) != entry.values.end();

  if (!contains) {
    return {};
  }

  return value;
}

}
