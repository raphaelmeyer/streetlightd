/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef PRESENTATION
#define PRESENTATION

#include "../application/IncomingMessage.h"
#include "../application/OutgoingMessage.h"

#include <functional>
#include <string>

namespace Presentation
{

  typedef std::function<std::string(const Outgoing::Message &message)> Encoder;
  typedef std::function<Incoming::Message(const std::string &message)> Decoder;
  typedef std::pair<Encoder,Decoder>  EncoderAndDecoder;

}

#endif

