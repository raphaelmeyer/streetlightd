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
#include "PrintFormat.h"

#include <functional>
#include <string>
#include <memory>

#include <protocolstack/application/message/Printer.h>

class Presentation
{
public:
  typedef std::function<presentation::Message(const message::Outgoing &message)> Encoder;

  Presentation(presentation::PrintFormat *_printFormat, presentation::Parser *_parser) :
    printFormat{_printFormat},
    parser{_parser}
  {
  }

  presentation::Message encode(const message::Outgoing &message) const
  {
    message::Printer printer{*printFormat};
    message.accept(printer);
    return printFormat->message();
  }

  message::Incoming decode(const presentation::Message &message)
  {
    parser->reset(message);
    return presentation::decode(*parser);
  }

private:
  std::unique_ptr<presentation::PrintFormat> printFormat;
  std::unique_ptr<presentation::Parser> parser;

};


#endif

