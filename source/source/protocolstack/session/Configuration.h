/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef SESSION_CONFIGURATION_H
#define SESSION_CONFIGURATION_H

#include <string>

namespace session
{

class Configuration
{
public:
  std::string host{};
  std::string user{};
  std::string password{};
};

}

#endif
