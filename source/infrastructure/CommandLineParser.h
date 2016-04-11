/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include "Factory.h"
#include <application/Application.h>
#include <presentation/Presentation.h>
#include <session/Session.h>

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

  void printLayer(const std::string &name, const std::set<std::string> &list) const;
  void printList(const std::set<std::string> &list) const;

};

#endif
