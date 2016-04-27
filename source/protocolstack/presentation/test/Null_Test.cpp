/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../Null.h"

#include <protocolstack/application/message/Incoming.h>
#include <protocolstack/application/message/Outgoing.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(presentation_Null_Test, decoder_returns_empty_message)
{
  const auto message = presentation::null::decode("");

  ASSERT_FALSE(message.luminosity.isValid());
  ASSERT_FALSE(message.warning.isValid());
}

TEST(presentation_Null_Test, encoder_returns_empty_message)
{
  message::Outgoing message;
  message.brightness = 0;

  const auto result = presentation::null::encode(message);

  ASSERT_EQ(0, result.asBinary().size());
}
