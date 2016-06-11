/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../JsonParser.h"

#include <protocolstack/application/message/Incoming.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class JsonParser_Test :
    public testing::Test
{
public:
  presentation::json::Parser testee;
  double dvalue;
  std::string svalue;

};


TEST_F(JsonParser_Test, throws_error_for_invalid_format)
{
  ASSERT_THROW(testee.reset(""), std::invalid_argument);
  ASSERT_THROW(testee.reset("wrong"), std::invalid_argument);
}

TEST_F(JsonParser_Test, does_nothing_for_an_empty_message)
{
  testee.reset("{}");
  ASSERT_FALSE(testee.hasMore());

  testee.reset("null\n");
  ASSERT_FALSE(testee.hasMore());
}

TEST_F(JsonParser_Test, decode_luminosity)
{
  testee.reset("{\"luminosity\":0.41}");

  ASSERT_EQ(message::Property::Luminosity, testee.parseProperty());
}

TEST_F(JsonParser_Test, decode_double)
{
  testee.reset("{\"luminosity\":0.41}");
  testee.parseProperty();

  testee.parse(dvalue);

  ASSERT_EQ(0.41, dvalue);
}

TEST_F(JsonParser_Test, throws_error_for_invalid_key)
{
  testee.reset("{\"a-different-key\":0.23}");

  ASSERT_THROW(testee.parseProperty(), std::invalid_argument);
}

TEST_F(JsonParser_Test, decode_warning)
{
  testee.reset("{\"warning\":\"hello world\"}");

  ASSERT_EQ(message::Property::Warning, testee.parseProperty());
}

TEST_F(JsonParser_Test, decode_string)
{
  testee.reset("{\"warning\":\"hello world\"}");
  testee.parseProperty();

  testee.parse(svalue);

  ASSERT_EQ("hello world", svalue);
}

//TODO add test when reading a double but a string is provided
