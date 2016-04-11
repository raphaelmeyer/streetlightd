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
  const Outgoing::Message message{};

  ASSERT_EQ("", KeyValue::encode(message));
}

TEST(KeyValueEncoder_Test, encode_brightness)
{
  const Outgoing::Message message{{Outgoing::Type::Brightness, 0.78}};

  ASSERT_EQ("brightness 0.78\n", KeyValue::encode(message));
}
