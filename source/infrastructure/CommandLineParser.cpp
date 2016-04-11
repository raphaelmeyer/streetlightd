/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "CommandLineParser.h"

CommandLineParser::CommandLineParser(std::ostream &_output, Factory<Application *> &_application, Factory<Presentation::EncoderAndDecoder> &_presentation, Factory<Session *> &_session) :
  output{_output},
  applicationFactory{_application},
  presentationFactory{_presentation},
  sessionFactory{_session}
{
}

Configuration CommandLineParser::parse(const std::vector<std::string> &arguments)
{
  if (arguments.size() != 4) {
    output << "expecting the following arguments: <application> <presentation> <session>" << std::endl;
    printLayer("application", applicationFactory.workers());
    printLayer("presentation", presentationFactory.workers());
    printLayer("session", sessionFactory.workers());
    output << std::flush;

    return {};
  }

  Configuration result;
  result.application = applicationFactory.produce(arguments[1]);
  result.presentation = presentationFactory.produce(arguments[2]);
  result.session = sessionFactory.produce(arguments[3]);

  return result;
}

void CommandLineParser::printLayer(const std::string &name, const std::set<std::string> &list) const
{
  output << "  " << name << ":";
  printList(list);
  output << std::endl;
}

void CommandLineParser::printList(const std::set<std::string> &list) const
{
  for (const auto &product : list) {
    output << " " << product;
  }
}


Configuration::operator bool() const
{
  return bool(application) && bool(session);
}
