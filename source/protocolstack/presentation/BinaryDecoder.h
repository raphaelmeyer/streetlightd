/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef BINARYDECODER_H
#define BINARYDECODER_H

#include <protocolstack/application/message/Incoming.h>
#include <protocolstack/presentation/Message.h>

namespace Binary
{

message::Incoming decode(const presentation::Message &message);

}

#endif
