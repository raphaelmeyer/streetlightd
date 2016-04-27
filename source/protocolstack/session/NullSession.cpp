/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "NullSession.h"


void NullSession::send(const presentation::Message &)
{
}

void NullSession::setConfiguration(const SessionConfiguration &)
{
}

void NullSession::connect()
{
}

void NullSession::close()
{
}

void NullSession::setMessageCallback(Session::Callback)
{
}
