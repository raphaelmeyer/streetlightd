/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../BinaryDecoder.h"

#include <protocolstack/application/message/Incoming.h>
#include <protocolstack/application/message/propertyNumbers.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(BinaryDecoder_Test, throws_error_for_invalid_key)
{
  ASSERT_THROW(Binary::decode(std::vector<uint8_t>{100}), std::invalid_argument);
}

TEST(BinaryDecoder_Test, throws_error_when_double_value_is_missing)
{
  const auto key = message::propertyNumber(message::Property::Luminosity);

  ASSERT_THROW(Binary::decode(std::vector<uint8_t>{key}), std::invalid_argument);
}

TEST(BinaryDecoder_Test, throws_error_when_string_length_is_missing)
{
  const auto key = message::propertyNumber(message::Property::Warning);

  ASSERT_THROW(Binary::decode(std::vector<uint8_t>{key}), std::invalid_argument);
}

TEST(BinaryDecoder_Test, throws_error_when_string_length_is_too_big)
{
  const auto key = message::propertyNumber(message::Property::Warning);

  ASSERT_THROW(Binary::decode(std::vector<uint8_t>{key, 4, 'a', 'a', 'a'}), std::invalid_argument);
}

TEST(BinaryDecoder_Test, does_nothing_for_an_empty_message)
{
  ASSERT_NO_THROW(Binary::decode({}));
}

TEST(BinaryDecoder_Test, decode_double)
{
  const auto key = message::propertyNumber(message::Property::Luminosity);

  auto message = Binary::decode(std::vector<uint8_t>{key, 57});

  ASSERT_NEAR(0.57, message.luminosity(), 0.001);
}

TEST(BinaryDecoder_Test, decode_string)
{
  const auto key = message::propertyNumber(message::Property::Warning);

  auto message = Binary::decode(std::vector<uint8_t>{key, 4, 'd', 'o', 'h', '!'});

  ASSERT_EQ("doh!", message.warning());
}

TEST(BinaryDecoder_Test, decode_2_values)
{
  const auto key1 = message::propertyNumber(message::Property::Warning);
  const auto key2 = message::propertyNumber(message::Property::Luminosity);

  auto message = Binary::decode(std::vector<uint8_t>{key1, 4, 'd', 'o', 'h', '!', key2, 22});

  ASSERT_NEAR(0.22, message.luminosity(), 0.001);
  ASSERT_EQ("doh!", message.warning());
}
