/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../KeyValuePrintFormat.h"

#include <protocolstack/application/message/Property.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <vector>

class KeyValuePrintFormat_Test :
    public testing::Test
{
public:
  presentation::keyvalue::PrintFormat testee;
};

TEST_F(KeyValuePrintFormat_Test, encode_empty_message)
{
  testee.outgoingHeader();
  testee.footer();

  ASSERT_EQ("", testee.message().asString());
}

TEST_F(KeyValuePrintFormat_Test, encode_double)
{
  testee.value(false, message::Property::Brightness, 0.78);

  ASSERT_EQ("brightness 0.78\n", testee.message().asString());
}

TEST_F(KeyValuePrintFormat_Test, encode_string)
{
  testee.value(true, message::Property::Info, "hello world");

  ASSERT_EQ("info hello world\n", testee.message().asString());
}
