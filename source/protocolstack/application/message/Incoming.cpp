/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Incoming.h"

#include "format.h"
#include <vector>

std::ostream& operator<<(std::ostream &stream, const message::Incoming &message)
{
  std::vector<std::string> values{};
  addIfValid(values, "luminosity", message.luminosity);
  addIfValid(values, "warning", message.warning);

  stream << "message::Incoming(" << values << ")";
  return stream;
}
