/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef MESSAGE_PROPERTYNUMBERS_H
#define MESSAGE_PROPERTYNUMBERS_H

#include <protocolstack/application/message/Property.h>

#include <cstdint>

namespace message
{

uint8_t propertyNumber(message::Property property);

}

#endif
