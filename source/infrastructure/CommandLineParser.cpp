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

CommandLineParser::CommandLineParser(std::ostream &_output, Factory<Application *> &_application, Factory<Presentation::EncoderAndDecoder> &_presentation, Factory<Session *> &_session) :
  output{_output},
  applicationFactory{_application},
  presentationFactory{_presentation},
  sessionFactory{_session}
{
}

Configuration CommandLineParser::parse(const std::vector<std::string> &arguments)
{
  Poco::Util::OptionSet options;

  const std::string appopt{join(applicationFactory.workers())};
  const std::string presopt{join(presentationFactory.workers())};
  const std::string sessopt{join(sessionFactory.workers())};

  options.addOption(Poco::Util::Option{"help",         "h", "print this help", false});
  options.addOption(Poco::Util::Option{"application",  "a", "<application>:"+appopt, true}.argument("<application>"));
  options.addOption(Poco::Util::Option{"presentation", "p", "<presentation>:"+presopt, true}.argument("<presentation>"));
  options.addOption(Poco::Util::Option{"session",      "s", "<session>:"+sessopt, true}.argument("<session>"));
  options.addOption(Poco::Util::Option{"address",       "", "address to connect to", false}.argument("<address>"));
  options.addOption(Poco::Util::Option{"credential",    "", "credentials for connection", false}.argument("<credential>"));

  Poco::Util::OptionProcessor p1(options);
  p1.setUnixStyle(true);

  std::string application{};
  std::string presentation{};
  std::string session{};

  for (const auto &arg : arguments) {
    std::string name;
    std::string value;
    try {
      if (p1.process(arg, name, value)) {
        if (name == "help") {
          printHelp(options);
          return {};
        } else if (name == "application") {
          application = value;
        } else if (name == "presentation") {
          presentation = value;
        } else if (name == "session") {
          session = value;
        }
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

  Configuration result;
  result.application = applicationFactory.produce(application);
  result.presentation = presentationFactory.produce(presentation);
  result.session = sessionFactory.produce(session);

  return result;
}

void CommandLineParser::printHelp(const Poco::Util::OptionSet &options)
{
  Poco::Util::HelpFormatter formatter{options};
  formatter.setUnixStyle(true);
  formatter.format(output);
}

std::string CommandLineParser::join(const std::set<std::string> &list) const
{
  std::string result{};
  for (const auto &product : list) {
    result += " " + product;
  }
  return result;
}


Configuration::operator bool() const
{
  return bool(application) && bool(session);
}
