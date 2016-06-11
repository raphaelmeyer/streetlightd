/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../BinaryPrintFormat.h"

#include <protocolstack/application/message/Outgoing.h>
#include <protocolstack/application/message/propertyNumbers.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <vector>

class BinaryPrintFormat_Test :
    public testing::Test
{
public:
  presentation::binary::PrintFormat testee;
};

TEST_F(BinaryPrintFormat_Test, encode_empty_message)
{
  testee.outgoingHeader();
  testee.footer();

  ASSERT_EQ(std::vector<uint8_t>{}, testee.message().asBinary());
}

TEST_F(BinaryPrintFormat_Test, encode_positive_double_value)
{
  const auto key = message::propertyNumber(message::Property::Brightness);

  testee.value(false, message::Property::Brightness, 0.78);

  ASSERT_EQ(std::vector<uint8_t>({key, 78}), testee.message().asBinary());
}

TEST_F(BinaryPrintFormat_Test, encode_negative_double_value)
{
  const auto key = message::propertyNumber(message::Property::Proximity);

  testee.value(false, message::Property::Proximity, -0.33);

  ASSERT_EQ(std::vector<uint8_t>({key, 0xdf}), testee.message().asBinary());
}

TEST_F(BinaryPrintFormat_Test, encode_string)
{
  testee.value(true, message::Property::Info, "hi");

  ASSERT_EQ(std::vector<uint8_t>({1, 2, 'h', 'i'}), testee.message().asBinary());
}
