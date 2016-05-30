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

  MOCK_METHOD0(writeIncomingHeader, void());
  MOCK_METHOD0(writeOutgoingHeader, void());
  MOCK_METHOD0(writeFooter, void());
  MOCK_METHOD1(writeSeparator, void(bool));
  MOCK_METHOD1(writeKey, void(message::Property));
  MOCK_METHOD0(writeKeyValueSeparator, void());
  MOCK_METHOD1(writeValue, void(double));
  MOCK_METHOD1(writeValue, void(const std::string &));

};

#endif
