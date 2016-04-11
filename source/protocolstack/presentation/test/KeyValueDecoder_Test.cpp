/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../KeyValueDecoder.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

typedef Incoming::Message M;

TEST(KeyValueDecoder_Test, does_nothing_for_an_empty_message)
{
  ASSERT_EQ(M{}, KeyValue::decode(""));
  ASSERT_EQ(M{}, KeyValue::decode("\n"));
  ASSERT_EQ(M{}, KeyValue::decode("\n\n"));
  ASSERT_EQ(M{}, KeyValue::decode("  "));
  ASSERT_EQ(M{}, KeyValue::decode("  \n"));
}

TEST(KeyValueDecoder_Test, decode_luminosity)
{
  auto message = KeyValue::decode("luminosity 0.41\n");

  ASSERT_EQ(1, message.size());
  ASSERT_EQ(0.41, message[Incoming::Type::Luminosity]);
}

TEST(KeyValueDecoder_Test, does_not_call_luminosity_for_different_key)
{
  auto message = KeyValue::decode("a-different-key 0.23\n");

  ASSERT_EQ(M{}, message);
}

TEST(KeyValueDecoder_Test, uses_latest_specified_value)
{
  auto message = KeyValue::decode("luminosity 0\nluminosity 0.12\nluminosity 0.89\n");

  ASSERT_EQ(1, message.size());
  ASSERT_EQ(0.89, message[Incoming::Type::Luminosity]);
}
