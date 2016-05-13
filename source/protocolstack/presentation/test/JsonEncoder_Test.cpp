/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../JsonEncoder.h"

#include <protocolstack/application/message/Outgoing.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <vector>

TEST(JsonEncoder_Test, encode_empty_message)
{
  const message::Outgoing message{};

  ASSERT_EQ("{}", presentation::json::encode(message).asString());
}

TEST(JsonEncoder_Test, encode_brightness)
{
  message::Outgoing message{};
  message.brightness = 0.78;

  ASSERT_EQ("{\"brightness\":0.78}", presentation::json::encode(message).asString());
}

TEST(JsonEncoder_Test, encode_moisture)
{
  message::Outgoing message{};
  message.moisture = 0.78;

  ASSERT_EQ("{\"moisture\":0.78}", presentation::json::encode(message).asString());
}

TEST(JsonEncoder_Test, encode_info)
{
  message::Outgoing message{};
  message.info = "hello world";

  ASSERT_EQ("{\"info\":\"hello world\"}", presentation::json::encode(message).asString());
}

TEST(JsonEncoder_Test, encode_multiple_values)
{
  message::Outgoing message{};
  message.brightness = 0.78;
  message.moisture = 0.12;
  message.info = "hello world";

  ASSERT_EQ("{\"brightness\":0.78,\"moisture\":0.12,\"info\":\"hello world\"}", presentation::json::encode(message).asString());
}
