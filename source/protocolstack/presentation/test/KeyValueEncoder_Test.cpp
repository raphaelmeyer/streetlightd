/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../KeyValueEncoder.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <vector>

TEST(KeyValueEncoder_Test, encode_empty_message)
{
  const message::Outgoing message{};

  ASSERT_EQ("", presentation::keyvalue::encode(message));
}

TEST(KeyValueEncoder_Test, encode_brightness)
{
  message::Outgoing message{};
  message.brightness = 0.78;

  ASSERT_EQ("brightness 0.78\n", presentation::keyvalue::encode(message));
}

TEST(KeyValueEncoder_Test, encode_moisture)
{
  message::Outgoing message{};
  message.moisture = 0.123;

  ASSERT_EQ("moisture 0.123\n", presentation::keyvalue::encode(message));
}

TEST(KeyValueEncoder_Test, encode_info)
{
  message::Outgoing message{};
  message.info = "hello world";

  ASSERT_EQ("info hello world\n", presentation::keyvalue::encode(message));
}

TEST(KeyValueEncoder_Test, encode_multiple_values)
{
  message::Outgoing message{};
  message.brightness = 0.78;
  message.moisture = 0.123;

  ASSERT_EQ("brightness 0.78\nmoisture 0.123\n", presentation::keyvalue::encode(message));
}
