/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Null.h"

namespace session
{

void Null::send(const presentation::Message &)
{
}

void Null::setConfiguration(const session::Configuration &)
{
}

void Null::connect()
{
}

void Null::close()
{
}

void Null::setMessageCallback(Session::Callback)
{
}

}
