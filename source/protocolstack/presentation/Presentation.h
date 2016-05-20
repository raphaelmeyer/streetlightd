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
#include "Parser.h"
#include "Decoder.h"

#include <functional>
#include <string>
#include <memory>

class Presentation
{
public:
  typedef std::function<presentation::Message(const message::Outgoing &message)> Encoder;

  Presentation(Encoder _encoder, presentation::Parser *_parser) :
    encoder{_encoder},
    parser{_parser}
  {
  }

  presentation::Message encode(const message::Outgoing &message) const
  {
    return encoder(message);
  }

  message::Incoming decode(const presentation::Message &message)
  {
    parser->reset(message);
    return presentation::decode(*parser);
  }

private:
  Encoder encoder;
  std::unique_ptr<presentation::Parser> parser;

};


#endif

