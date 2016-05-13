/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef PRESENTATION_KEYVALUE_ENCODER_H
#define PRESENTATION_KEYVALUE_ENCODER_H

#include <protocolstack/application/message/Outgoing.h>

/**
 * Own representation of key-value pairs that never should be used.
 *
 * document := { entry }
 * entry := identifier value '\n'
 * value := identifier | number
 */

namespace presentation
{
namespace keyvalue
{

  std::string encode(const message::Outgoing &message);

}
}

#endif
