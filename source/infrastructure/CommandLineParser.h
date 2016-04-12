/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include "Factory.h"
#include <protocolstack/application/Application.h>
#include <protocolstack/presentation/Presentation.h>
#include <protocolstack/session/Session.h>

#include <Poco/Util/OptionSet.h>
#include <ostream>
#include <vector>
#include <set>
#include <string>

class Configuration
{
public:
  Application *application{nullptr};
  Presentation::EncoderAndDecoder presentation{};
  Session *session{nullptr};

  operator bool() const;
};

class CommandLineParser
{
public:
  CommandLineParser(std::ostream &output, Factory<Application*> &applicationFactory, Factory<Presentation::EncoderAndDecoder> &presentationFactory, Factory<Session*> &sessionFactory);

  Configuration parse(const std::vector<std::string> &arguments);

private:
  std::ostream &output;
  Factory<Application*> &applicationFactory;
  Factory<Presentation::EncoderAndDecoder> &presentationFactory;
  Factory<Session*> &sessionFactory;

  std::string join(const std::set<std::string> &list) const;

  void printHelp(const Poco::Util::OptionSet &options);

};

#endif
