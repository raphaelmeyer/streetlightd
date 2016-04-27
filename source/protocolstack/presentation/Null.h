/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef PRESENTATION_NULL_H
#define PRESENTATION_NULL_H

#include <protocolstack/application/message/Incoming.h>
#include <protocolstack/application/message/Outgoing.h>
#include <protocolstack/presentation/Message.h>

namespace presentation
{

namespace null
{

message::Incoming decode(const Message &message);
Message encode(const message::Outgoing &message);

}

}

#endif
