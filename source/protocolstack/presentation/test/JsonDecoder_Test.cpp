/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../JsonDecoder.h"

#include <protocolstack/application/message/Incoming.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(JsonDecoder_Test, throws_error_for_invalid_format)
{
  ASSERT_THROW(Json::decode(""), std::invalid_argument);
  ASSERT_THROW(Json::decode("wrong"), std::invalid_argument);
}

TEST(JsonDecoder_Test, does_nothing_for_an_empty_message)
{
  ASSERT_NO_THROW(Json::decode("{}"));
  ASSERT_NO_THROW(Json::decode("null\n"));
}

TEST(JsonDecoder_Test, decode_luminosity)
{
  auto message = Json::decode("{\"luminosity\":0.41}");

  ASSERT_EQ(0.41, message.luminosity());
}

TEST(JsonDecoder_Test, does_not_call_luminosity_for_different_key)
{
  auto message = Json::decode("{\"a-different-key\":0.23}");

  ASSERT_FALSE(message.luminosity.isValid());
}

TEST(JsonDecoder_Test, uses_latest_specified_value)
{
  auto message = Json::decode("{\"luminosity\":0,\"luminosity\":0.12,\"luminosity\":0.89}");

  ASSERT_EQ(0.89, message.luminosity());
}

TEST(JsonDecoder_Test, decode_warning_string)
{
  auto message = Json::decode("{\"warning\":\"hello world\"}");

  ASSERT_EQ("hello world", message.warning());
}

//TODO test for multiple values
