/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "infrastructure/SasToken.h"
#include "infrastructure/cli/CommandLineParser.h"

#include <Poco/Util/OptionSet.h>
#include <Poco/Util/OptionProcessor.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionException.h>
#include <Poco/Util/HelpFormatter.h>

#include <string>
#include <iostream>
#include <map>
#include <stdexcept>

class Configuration
{
public:
  std::string key;
  std::string scope;
  std::chrono::seconds expiration;
  bool absolute;

  operator bool() const
  {
    return !key.empty();
  }

};

static void printHelp(const Poco::Util::OptionSet &options)
{
  Poco::Util::HelpFormatter formatter{options};
  formatter.setWidth(120);
  formatter.setUsage("azure-sas-token --key=<> --scope=<> --expiration=<> [--absolute]");
  formatter.setUnixStyle(true);
  formatter.format(std::cout);
}

static Configuration parseCommandLine(const std::vector<std::string> &arguments)
{
  cli::CommandLineParserImplementation parser{std::cout};

  Poco::Util::OptionSet options{};
  options.addOption(Poco::Util::Option{"key",        "", "base64 encoded password", true}.argument("<key>"));
  options.addOption(Poco::Util::Option{"scope",      "", "url", true}.argument("<scope>"));
  options.addOption(Poco::Util::Option{"expiration", "", "expiration time in seconds from now", true}.argument("<expiration>"));
  options.addOption(Poco::Util::Option{"absolute",   "", "if given, expiration time not from now but from 1.1.1970", false});

  parser.parse(arguments, options);

  if (!parser.isValid()) {
    printHelp(options);
    return {};
  }

  Configuration result;
  result.key = parser.value("key");
  result.scope = parser.value("scope");
  result.expiration = std::chrono::seconds(std::stoul(parser.value("expiration")));
  result.absolute = parser.contains("absolute");

  return result;
}

static SasTokenFactory::Time dawnOfUnixTime()
{
  return SasTokenFactory::Time(std::chrono::seconds(0));
}

int main(int argc, char **argv)
{
  const std::vector<std::string> arguments{argv, argv+argc};
  const auto configuration = parseCommandLine(arguments);
  if (!configuration) {
    return -1;
  }

  const auto timeReader = configuration.absolute ? dawnOfUnixTime : SasTokenFactory::currentTimeReader();
  SasTokenFactory factory{configuration.key, configuration.scope, timeReader};
  factory.setValidityDuration(configuration.expiration);

  std::cout << factory.produce() << std::endl;

  return 0;
}
