/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef CLI_ENUMOPTION_H
#define CLI_ENUMOPTION_H

#include <Poco/Util/Option.h>
#include <string>
#include <set>

namespace cli
{

class EnumOption {
public:
  std::string longName;
  std::string shortName;
  std::set<std::string> values;

  Poco::Util::Option asOption() const;
};

}

#endif
