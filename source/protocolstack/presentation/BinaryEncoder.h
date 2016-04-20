/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef BINARYENCODER_H
#define BINARYENCODER_H

#include <protocolstack/application/message/Outgoing.h>
#include <protocolstack/presentation/Message.h>


/**
 * Own binary format.
 *
 * document := { entry }
 * entry := key value
 * key := Byte
 * value := part | string
 * part := Byte (0: 0.0; 255: 1.0)
 * string := length { Byte }
 * length := Byte
 *
 */

namespace Binary
{

presentation::Message encode(const message::Outgoing &message);

}

#endif
