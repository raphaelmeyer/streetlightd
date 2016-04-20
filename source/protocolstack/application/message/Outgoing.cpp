/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Outgoing.h"

#include "format.h"
#include <vector>

std::ostream& operator<<(std::ostream &stream, const message::Outgoing &message)
{
  std::vector<std::string> values{};
  addIfValid(values, "brightness", message.brightness);
  addIfValid(values, "info", message.info);

  stream << "message::Outgoing(" << values << ")";
  return stream;
}
