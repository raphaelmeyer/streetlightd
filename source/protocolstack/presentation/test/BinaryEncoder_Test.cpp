/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../BinaryEncoder.h"

#include <protocolstack/application/message/Outgoing.h>
#include <protocolstack/application/message/propertyNumbers.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <vector>

TEST(BinaryEncoder_Test, encode_empty_message)
{
  const message::Outgoing message{};

  ASSERT_EQ(std::vector<uint8_t>{}, presentation::binary::encode(message).asBinary());
}

TEST(BinaryEncoder_Test, encode_positive_double_values)
{
  const auto key = message::propertyNumber(message::Property::Brightness);
  message::Outgoing message{};

  message.brightness = 0;
  ASSERT_EQ(std::vector<uint8_t>({key, 0}), presentation::binary::encode(message).asBinary());

  message.brightness = 1;
  ASSERT_EQ(std::vector<uint8_t>({key, 100}), presentation::binary::encode(message).asBinary());

  message.brightness = 0.33;
  ASSERT_EQ(std::vector<uint8_t>({key, 33}), presentation::binary::encode(message).asBinary());
}

TEST(BinaryEncoder_Test, encode_negative_double_values)
{
  const auto key = message::propertyNumber(message::Property::Proximity);
  message::Outgoing message{};

  message.proximity = -0;
  ASSERT_EQ(std::vector<uint8_t>({key, 0}), presentation::binary::encode(message).asBinary());

  message.proximity = -1;
  ASSERT_EQ(std::vector<uint8_t>({key, 0x9c}), presentation::binary::encode(message).asBinary());

  message.proximity = -0.33;
  ASSERT_EQ(std::vector<uint8_t>({key, 0xdf}), presentation::binary::encode(message).asBinary());
}

TEST(BinaryEncoder_Test, encode_string)
{
  message::Outgoing message{};
  message.info = "hi";

  ASSERT_EQ(std::vector<uint8_t>({1, 2, 'h', 'i'}), presentation::binary::encode(message).asBinary());
}

TEST(BinaryEncoder_Test, encode_2_values)
{
  message::Outgoing message{};
  message.brightness = 0.78;
  message.info = "";

  ASSERT_EQ(std::vector<uint8_t>({0, 78, 1, 0}), presentation::binary::encode(message).asBinary());
}
