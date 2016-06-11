/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "PocoParser.h"

#include <Poco/Util/OptionSet.h>
#include <Poco/Util/OptionProcessor.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionException.h>
#include <Poco/Util/HelpFormatter.h>
#include <map>

namespace cli
{

PocoParser::PocoParser(std::ostream &_output) :
  output{_output}
{
}

void PocoParser::printHelp() const
{
  Poco::Util::HelpFormatter formatter{options};
  formatter.setWidth(120);
  formatter.setUnixStyle(true);
  formatter.format(output);
}

bool PocoParser::isValid() const
{
  return valid;
}

void PocoParser::parse(const std::vector<std::string> &arguments, const Poco::Util::OptionSet &options)
{
  this->options = options;
  valid = false;
  map.clear();

  Poco::Util::OptionProcessor p1(options);
  p1.setUnixStyle(true);

  for (const auto &arg : arguments) {
    std::string name;
    std::string value;
    try {
      if (p1.process(arg, name, value)) {
        map[name] = value;
      }
    } catch (Poco::Util::MissingArgumentException) {
      return;
    } catch (Poco::Util::UnknownOptionException) {
      return;
    }
  }

  try {
    p1.checkRequired();
  } catch (Poco::Util::MissingOptionException) {
    return;
  }

  valid = true;
}

std::string PocoParser::value(const std::string &key) const
{
  const auto pos = map.find(key);
  if (pos == map.end()) {
    throw std::invalid_argument("key not available: " + key);
  }
  return pos->second;
}

std::string PocoParser::value(const std::string &key, const std::string &def) const
{
  const auto pos = map.find(key);
  if (pos == map.end()) {
    return def;
  } else {
    return pos->second;
  }
}

bool PocoParser::contains(const std::string &key) const
{
  return map.find(key) != map.end();
}

}
