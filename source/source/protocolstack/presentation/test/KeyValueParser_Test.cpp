/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../KeyValueParser.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class KeyValueParser_Test :
    public testing::Test
{
public:
  presentation::keyvalue::Parser testee;
  double dvalue;
  std::string svalue;

};


TEST_F(KeyValueParser_Test, does_nothing_for_an_empty_message)
{
  testee.reset("");
  ASSERT_FALSE(testee.hasMore());

  testee.reset("\n");
  ASSERT_FALSE(testee.hasMore());

  testee.reset("\n\n");
  ASSERT_FALSE(testee.hasMore());

  testee.reset("  ");
  ASSERT_FALSE(testee.hasMore());

  testee.reset("  \n");
  ASSERT_FALSE(testee.hasMore());
}

TEST_F(KeyValueParser_Test, throws_error_for_unknown_property)
{
  testee.reset("unknown value");

  ASSERT_THROW(testee.parseProperty(), std::invalid_argument);
}

TEST_F(KeyValueParser_Test, withespace_between_key_and_value_are_removed)
{
  testee.reset("warning     test");

  testee.parseProperty();
  testee.parse(svalue);

  ASSERT_EQ("test", svalue);
}

TEST_F(KeyValueParser_Test, withespace_after_value_are_removed)
{
  testee.reset("warning test    ");
  testee.parseProperty();

  testee.parse(svalue);

  ASSERT_EQ("test", svalue);
}

TEST_F(KeyValueParser_Test, whitespaces_in_string_are_kept)
{
  testee.reset("warning a    b");
  testee.parseProperty();

  testee.parse(svalue);

  ASSERT_EQ("a    b", svalue);
}

TEST_F(KeyValueParser_Test, parse_empty_string_property)
{
  testee.reset("warning ");
  testee.parseProperty();

  testee.parse(svalue);

  ASSERT_EQ("", svalue);
}

TEST_F(KeyValueParser_Test, decode_warning)
{
  testee.reset("warning test");

  ASSERT_EQ(message::Property::Warning, testee.parseProperty());
}

TEST_F(KeyValueParser_Test, decode_luminosity)
{
  testee.reset("luminosity 0.41\n");

  ASSERT_EQ(message::Property::Luminosity, testee.parseProperty());
}

TEST_F(KeyValueParser_Test, decode_double)
{
  testee.reset("luminosity 0.41\n");
  testee.parseProperty();

  testee.parse(dvalue);

  ASSERT_EQ(0.41, dvalue);
}

TEST_F(KeyValueParser_Test, decode_2_values)
{
  testee.reset("luminosity 0.41\nwarning test");

  ASSERT_EQ(message::Property::Luminosity, testee.parseProperty());
  testee.parse(dvalue);

  ASSERT_EQ(message::Property::Warning, testee.parseProperty());
  testee.parse(svalue);

  ASSERT_FALSE(testee.hasMore());

  ASSERT_EQ(0.41, dvalue);
  ASSERT_EQ("test", svalue);
}

//TODO add test when reading a double but a string is provided
