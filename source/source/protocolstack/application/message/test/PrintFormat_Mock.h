/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef MESSAGE_VISITOR_MOCK
#define MESSAGE_VISITOR_MOCK

#include "../PrintFormat.h"

#include <gmock/gmock.h>

class PrintFormatMock :
    public message::PrintFormat
{
public:

  MOCK_METHOD0(incomingHeader, void());
  MOCK_METHOD0(outgoingHeader, void());
  MOCK_METHOD0(footer, void());
  MOCK_METHOD3(value, void(bool, message::Property, double));
  MOCK_METHOD3(value, void(bool, message::Property, const std::string &));

};

#endif
