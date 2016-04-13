/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "CommandLineParser.h"

#include <Poco/Util/OptionSet.h>
#include <Poco/Util/OptionProcessor.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionException.h>
#include <Poco/Util/HelpFormatter.h>
#include <map>

CommandLineParser::CommandLineParser(std::ostream &_output) :
  output{_output}
{
  enums[Layer::Application] = EnumEntry{"application", "a", {}};
  enums[Layer::Presentation] = EnumEntry{"presentation", "p", {}};
  enums[Layer::Session] = EnumEntry{"session", "s", {}};
}

void CommandLineParser::addApplications(const std::set<std::string> &values)
{
  enums[Layer::Application].values.insert(values.begin(), values.end());
}

void CommandLineParser::addPresentations(const std::set<std::string> &values)
{
  enums[Layer::Presentation].values.insert(values.begin(), values.end());
}

void CommandLineParser::addSessions(const std::set<std::string> &values)
{
  enums[Layer::Session].values.insert(values.begin(), values.end());
}

Configuration CommandLineParser::parse(const std::vector<std::string> &arguments) const
{
  const Poco::Util::OptionSet options = createOptions();

   auto values = parseToMap(arguments, options);  //TODO make const again

  if (values.empty()) {
    printHelp(options);
    return {};
  }

  auto enumValues = fillEnumValues(values);
  if (enumValues.empty()) {
    printHelp(options);
    return {};
  }

  if (values.find("help") != values.end()) {
    printHelp(options);
    return {};
  }

  Configuration config{};
  fillStackConfig(config, enumValues);
  fillSessionConfig(config, values);
  fillTimerConfig(config, values);
  return config;
}

std::map<std::string, std::string> CommandLineParser::parseToMap(const std::vector<std::string> &arguments, const Poco::Util::OptionSet &options) const
{
  Poco::Util::OptionProcessor p1(options);
  p1.setUnixStyle(true);

  std::map<std::string, std::string> values;

  for (const auto &arg : arguments) {
    std::string name;
    std::string value;
    try {
      if (p1.process(arg, name, value)) {
        values[name] = value;
      }
    } catch (Poco::Util::MissingArgumentException e) {
      return {};
    }
  }

  try {
    p1.checkRequired();
  } catch (Poco::Util::MissingOptionException e) {
    return {};
  }

  return values;
}

std::map<CommandLineParser::Layer,std::string> CommandLineParser::fillEnumValues(const std::map<std::string, std::string> &values) const
{
  std::map<Layer,std::string> enumValues{};
  for (const auto layer : {Layer::Application, Layer::Presentation, Layer::Session}) {
    const auto value = valueFor(layer, values);
    if (value.empty()) {
      return {};
    }
    enumValues[layer] = value;
  }

  return enumValues;
}

void CommandLineParser::fillStackConfig(StackConfiguration &config, std::map<Layer, std::string> enumValues) const
{
  config.application = enumValues[Layer::Application];
  config.presentation = enumValues[Layer::Presentation];
  config.session = enumValues[Layer::Session];
}

void CommandLineParser::fillSessionConfig(SessionConfiguration &config, std::map<std::string, std::string> values) const
{
  config.address = values["address"];
  config.credential = values["credential"];
}

void CommandLineParser::fillTimerConfig(TimerConfiguration &config, std::map<std::string, std::string> values) const
{
  config.externalTimer = values.find("external-timer") != values.end();
}

Poco::Util::OptionSet CommandLineParser::createOptions() const
{
  Poco::Util::OptionSet options{};

  options.addOption(Poco::Util::Option{"help",         "h", "print this help", false});

  for (const auto &opt : enums) {
    options.addOption(opt.second.asOption());
  }

  options.addOption(Poco::Util::Option{"address",        "", "address to connect to", false}.argument("<address>"));
  options.addOption(Poco::Util::Option{"credential",     "", "credentials for connection", false}.argument("<credential>"));
  options.addOption(Poco::Util::Option{"external-timer", "", "trigger updates via DBus", false});
  return options;
}

void CommandLineParser::printHelp(const Poco::Util::OptionSet &options) const
{
  Poco::Util::HelpFormatter formatter{options};
  formatter.setUnixStyle(true);
  formatter.format(output);
}

std::string CommandLineParser::keyFor(CommandLineParser::Layer entry) const
{
  const auto &pos = enums.find(entry);
  if (pos == enums.end()) {
    throw std::runtime_error("entry not defined: " + std::to_string(int(entry)));
  }
  return pos->second.longName;
}

CommandLineParser::EnumEntry CommandLineParser::entryFor(CommandLineParser::Layer entry) const
{
  const auto &pos = enums.find(entry);
  if (pos == enums.end()) {
    throw std::runtime_error("entry not defined: " + std::to_string(int(entry)));
  }
  return pos->second;
}

std::string CommandLineParser::valueFor(CommandLineParser::Layer type, const std::map<std::string, std::string> &values) const
{
  EnumEntry entry = entryFor(type);
  const auto &pos = values.find(entry.longName);

  if (pos == values.end()) {
    return {};
  }

  const auto value = pos->second;
  const auto contains = entry.values.find(value) != entry.values.end();

  if (!contains) {
    return {};
  }

  return value;
}


static std::string join(const std::set<std::string> &list)
{
  std::string result{};
  for (const auto &product : list) {
    result += " " + product;
  }
  return result;
}

Poco::Util::Option CommandLineParser::EnumEntry::asOption() const
{
  const std::string argument{"<"+longName+">"};
  const std::string help{argument + ":" + join(values)};
  return Poco::Util::Option{longName,  shortName, help, true}.argument(argument);
}
