/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef JSONDECODER_H
#define JSONDECODER_H

#include <protocolstack/application/message/Incoming.h>

#include <string>

namespace Json
{

  message::Incoming decode(const std::string &message);

}

#endif
