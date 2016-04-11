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

void CommandLineParser::parse(const std::vector<std::string> &arguments)
{
  if (arguments.size() != 4) {
    output << "expecting the following arguments: <application> <presentation> <session>" << std::endl;
    printLayer("application", applicationFactory.workers());
    printLayer("presentation", presentationFactory.workers());
    printLayer("session", sessionFactory.workers());
    return;
  }

  application = applicationFactory.produce(arguments[1]);
  presentation = presentationFactory.produce(arguments[2]);
  session = sessionFactory.produce(arguments[3]);
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

Application *CommandLineParser::getApplication() const
{
  return application;
}

Presentation::EncoderAndDecoder CommandLineParser::getPresentation() const
{
  return presentation;
}

Session *CommandLineParser::getSession() const
{
  return session;
}

