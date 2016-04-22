/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../BinaryEncoder.h"

#include <protocolstack/application/message/Outgoing.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <vector>

TEST(BinaryEncoder_Test, encode_empty_message)
{
  const message::Outgoing message{};

  ASSERT_EQ(std::vector<uint8_t>{}, Binary::encode(message).asBinary());
}

TEST(BinaryEncoder_Test, encode_brightness)
{
  message::Outgoing message{};
  message.brightness = 0.25;

  ASSERT_EQ(std::vector<uint8_t>({0, 64}), Binary::encode(message).asBinary());
}

TEST(BinaryEncoder_Test, encode_moisture)
{
  message::Outgoing message{};
  message.moisture = 0.5;

  ASSERT_EQ(std::vector<uint8_t>({4, 128}), Binary::encode(message).asBinary());
}

TEST(BinaryEncoder_Test, encode_info)
{
  message::Outgoing message{};
  message.info = "hi";

  ASSERT_EQ(std::vector<uint8_t>({1, 2, 'h', 'i'}), Binary::encode(message).asBinary());
}

TEST(BinaryEncoder_Test, encode_2_values)
{
  message::Outgoing message{};
  message.brightness = 0.78;
  message.info = "";

  ASSERT_EQ(std::vector<uint8_t>({0, 199, 1, 0}), Binary::encode(message).asBinary());
}
