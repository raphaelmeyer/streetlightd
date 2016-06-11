/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Message.h"

#include "Printer.h"
#include "DebugFormat.h"
#include "propertyNames.h"

std::ostream& operator<<(std::ostream &stream, const message::Message &message)
{
  message::DebugFormat format{stream};
  message::Printer printer{format};

  message.accept(printer);

  return stream;
}

