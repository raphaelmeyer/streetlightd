/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../JsonPrintFormat.h"

#include <protocolstack/application/message/Outgoing.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <vector>

class JsonPrintFormat_Test :
    public testing::Test
{
public:
  presentation::json::PrintFormat testee;
};

TEST_F(JsonPrintFormat_Test, encode_empty_message)
{
  testee.outgoingHeader();
  testee.footer();

  ASSERT_EQ("{}", testee.message().asString());
}

TEST_F(JsonPrintFormat_Test, encode_double)
{
  testee.value(true, message::Property::Brightness, 0.78);

  ASSERT_EQ("\"brightness\":0.78", testee.message().asString());
}

TEST_F(JsonPrintFormat_Test, encode_string)
{
  testee.value(true, message::Property::Info, "hello world");

  ASSERT_EQ("\"info\":\"hello world\"", testee.message().asString());
}

TEST_F(JsonPrintFormat_Test, add_semicolon_as_separator)
{
  testee.value(false, message::Property::Info, "hello world");

  ASSERT_EQ(",\"info\":\"hello world\"", testee.message().asString());
}

TEST_F(JsonPrintFormat_Test, encode_full)
{
  testee.outgoingHeader();
  testee.value(true, message::Property::Brightness, 0.78);
  testee.value(false, message::Property::Moisture, 0.12);
  testee.value(false, message::Property::Info, "hello world");
  testee.footer();

  ASSERT_EQ("{\"brightness\":0.78,\"moisture\":0.12,\"info\":\"hello world\"}", testee.message().asString());
}
