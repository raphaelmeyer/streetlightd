/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef PRESENTATION_KEYVALUE_ENCODER_H
#define PRESENTATION_KEYVALUE_ENCODER_H

#include <protocolstack/application/message/Outgoing.h>
#include <protocolstack/presentation/Message.h>

namespace presentation
{
namespace keyvalue
{

  presentation::Message encode(const message::Outgoing &message);

}
}

#endif
