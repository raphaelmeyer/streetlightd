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
}

void CommandLineParser::addApplications(const std::set<std::string> &values)
{
  application.insert(values.begin(), values.end());
}

void CommandLineParser::addPresentations(const std::set<std::string> &values)
{
  presentation.insert(values.begin(), values.end());
}

void CommandLineParser::addSessions(const std::set<std::string> &values)
{
  session.insert(values.begin(), values.end());
}

static std::string join(const std::set<std::string> &list)
{
  std::string result{};
  for (const auto &product : list) {
    result += " " + product;
  }
  return result;
}

static Poco::Util::Option layerOption(const std::string &longName, const std::string &shortName, const std::set<std::string> &values)
{
  const std::string argument{"<"+longName+">"};
  const std::string help{argument + ":" + join(values)};
  return Poco::Util::Option{longName,  shortName, help, true}.argument(argument);
}

Configuration CommandLineParser::parse(const std::vector<std::string> &arguments)
{
  //TODO cleanup
  Poco::Util::OptionSet options;

  options.addOption(Poco::Util::Option{"help",         "h", "print this help", false});
  options.addOption(layerOption("application", "a", application));
  options.addOption(layerOption("presentation", "p", presentation));
  options.addOption(layerOption("session", "s", session));
  options.addOption(Poco::Util::Option{"address",       "", "address to connect to", false}.argument("<address>"));
  options.addOption(Poco::Util::Option{"credential",    "", "credentials for connection", false}.argument("<credential>"));

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
      printHelp(options);
      return {};
    }
  }

  try {
    p1.checkRequired();
  } catch (Poco::Util::MissingOptionException e) {
    printHelp(options);
    return {};
  }

  if (values.find("help") != values.end()) {
    printHelp(options);
    return {};
  }

  Configuration configuration;

  configuration.application = values["application"];
  configuration.presentation = values["presentation"];
  configuration.session = values["session"];

  return configuration;
}

void CommandLineParser::printHelp(const Poco::Util::OptionSet &options)
{
  Poco::Util::HelpFormatter formatter{options};
  formatter.setUnixStyle(true);
  formatter.format(output);
}

Configuration::operator bool() const
{
  return !application.empty() && !presentation.empty() && !session.empty();
}
