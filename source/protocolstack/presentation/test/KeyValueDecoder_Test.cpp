/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../KeyValueDecoder.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(KeyValueDecoder_Test, does_nothing_for_an_empty_message)
{
  ASSERT_NO_THROW(presentation::keyvalue::decode(""));
  ASSERT_NO_THROW(presentation::keyvalue::decode("\n"));
  ASSERT_NO_THROW(presentation::keyvalue::decode("\n\n"));
  ASSERT_NO_THROW(presentation::keyvalue::decode("  "));
  ASSERT_NO_THROW(presentation::keyvalue::decode("  \n"));
}

TEST(KeyValueDecoder_Test, does_nothing_for_wrong_format)
{
  ASSERT_NO_THROW(presentation::keyvalue::decode("one-word\n"));
  ASSERT_NO_THROW(presentation::keyvalue::decode("two words\n"));
  ASSERT_FALSE(presentation::keyvalue::decode("luminosity not-a-double\n").luminosity.isValid());
}

TEST(KeyValueDecoder_Test, last_newline_can_be_omitted)
{
  auto message = presentation::keyvalue::decode("luminosity 0.41");

  ASSERT_EQ(0.41, message.luminosity());
}

TEST(KeyValueDecoder_Test, withespace_between_key_and_value_are_removed)
{
  auto message = presentation::keyvalue::decode("warning     test");

  ASSERT_EQ("test", message.warning());
}

TEST(KeyValueDecoder_Test, withespace_after_value_are_removed)
{
  auto message = presentation::keyvalue::decode("warning test    ");

  ASSERT_EQ("test", message.warning());
}

TEST(KeyValueDecoder_Test, decode_warning_with_whitespaces)
{
  auto message = presentation::keyvalue::decode("warning a    b");

  ASSERT_EQ("a    b", message.warning());
}

TEST(KeyValueDecoder_Test, decode_warning_string)
{
  auto message = presentation::keyvalue::decode("warning test\n");

  ASSERT_EQ("test", message.warning());
}

TEST(KeyValueDecoder_Test, decode_luminosity)
{
  auto message = presentation::keyvalue::decode("luminosity 0.41\n");

  ASSERT_EQ(0.41, message.luminosity());
}

TEST(KeyValueDecoder_Test, uses_latest_specified_value)
{
  auto message = presentation::keyvalue::decode("luminosity 0\nluminosity 0.12\nluminosity 0.89\n");

  ASSERT_EQ(0.89, message.luminosity());
}
