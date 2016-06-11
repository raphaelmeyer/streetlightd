/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef PRESENTATION_DECODER_H
#define PRESENTATION_DECODER_H

#include "Parser.h"

#include <protocolstack/application/message/Incoming.h>
#include <protocolstack/presentation/Message.h>

namespace presentation
{

message::Incoming decode(Parser &parser);

}

#endif
