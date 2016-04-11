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
#include <application/Presentation.h>
#include <presentation/Session.h>

#include <ostream>
#include <vector>
#include <set>
#include <string>

class CommandLineParser
{
public:
  CommandLineParser(std::ostream &output, Factory<Application> &applicationFactory, Factory<Presentation> &presentationFactory, Factory<Session> &sessionFactory);

  void parse(const std::vector<std::string> &arguments);

  Application *getApplication() const;
  Presentation *getPresentation() const;
  Session *getSession() const;

private:
  std::ostream &output;
  Factory<Application> &applicationFactory;
  Factory<Presentation> &presentationFactory;
  Factory<Session> &sessionFactory;

  Application *application{nullptr};
  Presentation *presentation{nullptr};
  Session *session{nullptr};

  void printLayer(const std::string &name, const std::set<std::string> &list) const;
  void printList(const std::set<std::string> &list) const;

};

#endif
