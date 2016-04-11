/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef KEYVALUEDECODER_H
#define KEYVALUEDECODER_H

#include <protocolstack/application/IncomingMessage.h>

#include <string>

namespace KeyValue
{

  Incoming::Message decode(const std::string &message);

}

#endif
