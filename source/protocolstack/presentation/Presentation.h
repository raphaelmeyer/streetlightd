/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef PRESENTATION
#define PRESENTATION

#include "../application/message/Incoming.h"
#include "../application/message/Outgoing.h"

#include <functional>
#include <string>

namespace Presentation
{

  typedef std::function<std::string(const message::Outgoing &message)> Encoder;
  typedef std::function<message::Incoming(const std::string &message)> Decoder;
  typedef std::pair<Encoder,Decoder>  EncoderAndDecoder;

}

#endif

