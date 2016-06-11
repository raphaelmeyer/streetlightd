/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Parser_Dummy.h"

namespace cli
{

void ParserDummy::parse(const std::vector<std::string> &, const Poco::Util::OptionSet &options)
{
  parseOptions = options;
}

void ParserDummy::printHelp() const
{
}

bool ParserDummy::isValid() const
{
  return {};
}

std::string ParserDummy::value(const std::string &) const
{
  return {};
}

std::string ParserDummy::value(const std::string &, const std::string &) const
{
  return {};
}

bool ParserDummy::contains(const std::string &) const
{
  return {};
}


}
