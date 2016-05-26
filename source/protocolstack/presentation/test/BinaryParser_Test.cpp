/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../BinaryParser.h"

#include <protocolstack/application/message/Incoming.h>
#include <protocolstack/application/message/propertyNumbers.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class BinaryParser_Test :
    public testing::Test
{
public:
  presentation::binary::Parser testee;
  double dvalue;
  std::string svalue;

};

TEST_F(BinaryParser_Test, throws_error_for_invalid_key)
{
  testee.reset(std::vector<uint8_t>{100});

  ASSERT_THROW(testee.parseProperty(), std::invalid_argument);
}

TEST_F(BinaryParser_Test, throws_error_when_double_value_is_missing)
{
  const auto key = message::propertyNumber(message::Property::Luminosity);
  testee.reset(std::vector<uint8_t>{key});

  testee.parseProperty();

  ASSERT_THROW(testee.parse(dvalue), std::invalid_argument);
}

TEST_F(BinaryParser_Test, throws_error_when_string_length_is_missing)
{
  const auto key = message::propertyNumber(message::Property::Warning);
  testee.reset(std::vector<uint8_t>{key});

  testee.parseProperty();

  ASSERT_THROW(testee.parse(svalue), std::invalid_argument);
}

TEST_F(BinaryParser_Test, throws_error_when_string_length_is_too_big)
{
  const auto key = message::propertyNumber(message::Property::Warning);
  testee.reset(std::vector<uint8_t>{key, 4, 'a', 'a', 'a'});

  testee.parseProperty();

  ASSERT_THROW(testee.parse(svalue), std::invalid_argument);
}

TEST_F(BinaryParser_Test, an_empty_message_is_valid)
{
  testee.reset(std::vector<uint8_t>{});

  ASSERT_FALSE(testee.hasMore());
}

TEST_F(BinaryParser_Test, decode_luminosity)
{
  const auto key = message::propertyNumber(message::Property::Luminosity);
  testee.reset(std::vector<uint8_t>{key, 57});

  ASSERT_EQ(message::Property::Luminosity, testee.parseProperty());
}

TEST_F(BinaryParser_Test, decode_double)
{
  const auto key = message::propertyNumber(message::Property::Luminosity);
  testee.reset(std::vector<uint8_t>{key, 57});
  testee.parseProperty();

  testee.parse(dvalue);

  ASSERT_NEAR(0.57, dvalue, 0.001);
}

TEST_F(BinaryParser_Test, decode_warning)
{
  const auto key = message::propertyNumber(message::Property::Warning);
  testee.reset(std::vector<uint8_t>{key, 4, 'd', 'o', 'h', '!'});

  ASSERT_EQ(message::Property::Warning, testee.parseProperty());
}

TEST_F(BinaryParser_Test, decode_string)
{
  const auto key = message::propertyNumber(message::Property::Warning);
  testee.reset(std::vector<uint8_t>{key, 4, 'd', 'o', 'h', '!'});
  testee.parseProperty();

  testee.parse(svalue);

  ASSERT_EQ("doh!", svalue);
}

TEST_F(BinaryParser_Test, decode_2_values)
{
  const auto key1 = message::propertyNumber(message::Property::Warning);
  const auto key2 = message::propertyNumber(message::Property::Luminosity);
  testee.reset(std::vector<uint8_t>{key1, 4, 'd', 'o', 'h', '!', key2, 22});

  ASSERT_EQ(message::Property::Warning, testee.parseProperty());
  testee.parse(svalue);

  ASSERT_EQ(message::Property::Luminosity, testee.parseProperty());
  testee.parse(dvalue);

  ASSERT_FALSE(testee.hasMore());

  ASSERT_NEAR(0.22, dvalue, 0.001);
  ASSERT_EQ("doh!", svalue);
}

//TODO add test when reading a double but a string is provided
