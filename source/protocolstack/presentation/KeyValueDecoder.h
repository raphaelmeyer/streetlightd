/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef PRESENTATION_KEYVALUE_DECODER_H
#define PRESENTATION_KEYVALUE_DECODER_H

#include <protocolstack/application/message/Incoming.h>
#include <protocolstack/presentation/Message.h>

namespace presentation
{
namespace keyvalue
{

  message::Incoming decode(const presentation::Message &message);

}
}

#endif
