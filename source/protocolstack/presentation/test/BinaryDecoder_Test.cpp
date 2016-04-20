/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../BinaryDecoder.h"

#include <protocolstack/application/message/Incoming.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(BinaryDecoder_Test, throws_error_for_invalid_key)
{
  ASSERT_THROW(Binary::decode(std::vector<uint8_t>{100}), std::invalid_argument);
}

TEST(BinaryDecoder_Test, throws_error_when_luminosity_value_is_missing)
{
  ASSERT_THROW(Binary::decode(std::vector<uint8_t>{2}), std::invalid_argument);
}

TEST(BinaryDecoder_Test, throws_error_when_string_length_is_missing)
{
  ASSERT_THROW(Binary::decode(std::vector<uint8_t>{3}), std::invalid_argument);
}

TEST(BinaryDecoder_Test, throws_error_when_string_length_is_too_big)
{
  ASSERT_THROW(Binary::decode(std::vector<uint8_t>{3, 4, 'a', 'a', 'a'}), std::invalid_argument);
}

TEST(BinaryDecoder_Test, does_nothing_for_an_empty_message)
{
  ASSERT_NO_THROW(Binary::decode({}));
}

TEST(BinaryDecoder_Test, decode_luminosity)
{
  auto message = Binary::decode(std::vector<uint8_t>{2, 105});

  ASSERT_NEAR(0.41, message.luminosity(), 0.01);
}

TEST(BinaryDecoder_Test, decode_warning_string)
{
  auto message = Binary::decode(std::vector<uint8_t>{3, 4, 'd', 'o', 'h', '!'});

  ASSERT_EQ("doh!", message.warning());
}

TEST(BinaryDecoder_Test, decode_2_values)
{
  auto message = Binary::decode(std::vector<uint8_t>{3, 4, 'd', 'o', 'h', '!', 2, 105});

  ASSERT_NEAR(0.41, message.luminosity(), 0.01);
  ASSERT_EQ("doh!", message.warning());
}
