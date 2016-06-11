/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../Value.h"

#include <gtest/gtest.h>

TEST(message_Value_Test, is_not_valid_by_default)
{
  message::Value<int> testee{};

  ASSERT_FALSE(testee.isValid());
}

TEST(message_Value_Test, is_valid_when_constructed_with_value)
{
  message::Value<int> testee{42};

  ASSERT_TRUE(testee());
}

TEST(message_Value_Test, can_read_value)
{
  ASSERT_EQ(42, message::Value<int>{42}());
  ASSERT_EQ("hello", message::Value<std::string>{"hello"}());
}

TEST(message_Value_Test, is_valid_when_setting_value)
{
  message::Value<int> testee{};

  testee = 42;

  ASSERT_TRUE(testee.isValid());
}

TEST(message_Value_Test, can_store_value)
{
  message::Value<int> testee{};

  testee = 42;

  ASSERT_EQ(42, testee());
}

TEST(message_Value_Test, read_while_invalid_is_not_allowed)
{
  message::Value<int> testee{};

  ASSERT_THROW(testee(), std::runtime_error);
}

TEST(message_Value_Test, can_print_valid_value_to_stream)
{
  std::stringstream stream;
  message::Value<int> testee{42};

  stream << testee;

  ASSERT_EQ("42", stream.str());
}

TEST(message_Value_Test, can_print_invalid_value_to_stream)
{
  std::stringstream stream;
  message::Value<int> testee{};

  stream << testee;

  ASSERT_EQ("invalid", stream.str());
}
