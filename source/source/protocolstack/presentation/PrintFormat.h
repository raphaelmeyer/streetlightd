/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef PRESENTATION_PRINTFORMAT_H
#define PRESENTATION_PRINTFORMAT_H

#include <protocolstack/presentation/Message.h>
#include <protocolstack/application/message/PrintFormat.h>

namespace presentation
{

class PrintFormat :
    public message::PrintFormat
{
public:
  virtual ~PrintFormat() = default;

  virtual presentation::Message message() const = 0;

};

}

#endif
