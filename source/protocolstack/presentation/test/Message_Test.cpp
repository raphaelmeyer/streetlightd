/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../Message.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(Message_Test, has_default_constuctor)
{
  presentation::Message message{};

  ASSERT_EQ("", message.asString());
}

TEST(Message_Test, can_create_from_string)
{
  std::string string{"hello world"};

  presentation::Message message{string};

  ASSERT_EQ("hello world", message.asString());
}

TEST(Message_Test, can_create_from_char_pointer)
{
  const char *pointer = "hello world";

  presentation::Message message{pointer};

  ASSERT_EQ("hello world", message.asString());
}

TEST(Message_Test, can_create_from_void_pointer_with_length)
{
  const void *pointer = "hello world";
  const size_t length = 11;

  presentation::Message message{pointer, length};

  ASSERT_EQ("hello world", message.asString());
}

TEST(Message_Test, can_create_from_vector)
{
  const std::vector<uint8_t> data{10, 20, 30, 40};

  presentation::Message message{data};

  ASSERT_EQ(data, message.asBinary());
}

TEST(Message_Test, can_extract_message_as_string)
{
  presentation::Message message{"hello world"};

  ASSERT_EQ("hello world", message.asString());
}

TEST(Message_Test, can_extract_message_as_binary)
{
  const std::vector<std::uint8_t> expected{'h', 'e', 'l', 'l', 'o'};

  presentation::Message message{"hello"};

  ASSERT_EQ(expected, message.asBinary());
}

