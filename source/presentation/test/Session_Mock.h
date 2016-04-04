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
  MOCK_METHOD0(setUp, void());
  MOCK_METHOD0(connect, void());
  MOCK_METHOD1(send, void(const std::string &));
  MOCK_METHOD1(subscribe, void(const std::string&));
  MOCK_METHOD0(close, void());
  MOCK_METHOD1(setMessageCallback, void(std::function<void(const std::string&)>));

};

#endif

