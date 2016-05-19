/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "EnumOption.h"

#include <map>

namespace cli
{

static std::string join(const std::set<std::string> &list)
{
  std::string result{};
  for (const auto &product : list) {
    result += " " + product;
  }
  return result;
}

Poco::Util::Option EnumOption::asOption() const
{
  const std::string argument{"<"+longName+">"};
  const std::string help{argument + ":" + join(values)};
  return Poco::Util::Option{longName,  shortName, help, true}.argument(argument);
}

}
