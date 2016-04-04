/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef SESSION_MOCK
#define SESSION_MOCK

#include "../Session.h"

#include <gmock/gmock.h>

class SessionMock :
    public Session
{
public:
  MOCK_METHOD1(send, void(const std::string &));

};

#endif

