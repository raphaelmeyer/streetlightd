/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef SESSIONCONFIGURATION_H
#define SESSIONCONFIGURATION_H

#include <string>

class SessionConfiguration
{
public:
  std::string address{};
  std::string credential{};
};

#endif
