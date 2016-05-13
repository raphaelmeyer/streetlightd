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
#include "Message.h"

#include <functional>
#include <string>

class Presentation
{
public:
  typedef std::function<presentation::Message(const message::Outgoing &message)> Encoder;
  typedef std::function<message::Incoming(const presentation::Message &message)> Decoder;

  Presentation(Encoder _encoder, Decoder _decoder) :
    encoder{_encoder},
    decoder{_decoder}
  {
  }

  presentation::Message encode(const message::Outgoing &message) const
  {
    return encoder(message);
  }

  message::Incoming decode(const presentation::Message &message) const
  {
    return decoder(message);
  }

private:
  Encoder encoder;
  Decoder decoder;

};


#endif

