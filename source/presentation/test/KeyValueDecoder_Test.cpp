/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../KeyValueDecoder.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>


class KeyValueDecoder_Test:
    public testing::Test
{
public:
  typedef std::vector<double> vd;

  void SetUp() override
  {
    testee.setListener([this](double luminosity){
      luminosities.push_back(luminosity);
    });
  }

  KeyValueDecoder testee{};
  vd luminosities;

};

TEST_F(KeyValueDecoder_Test, does_nothing_for_an_empty_message)
{
  testee.decode("");
  testee.decode("\n");
  testee.decode("\n\n");
  testee.decode("  ");
  testee.decode("  \n");

  ASSERT_EQ(vd{}, luminosities);
}

TEST_F(KeyValueDecoder_Test, decode_luminosity)
{
  testee.decode("luminosity 0.41\n");

  ASSERT_EQ(vd{0.41}, luminosities);
}

TEST_F(KeyValueDecoder_Test, does_not_call_luminosity_for_different_key)
{
  testee.decode("a-different-key 0.23\n");

  ASSERT_EQ(vd{}, luminosities);
}

TEST_F(KeyValueDecoder_Test, calls_method_as_often_as_the_key_occurs)
{
  testee.decode("luminosity 0\nluminosity 0.12\nluminosity 0.89\n");

  ASSERT_EQ(vd({0, 0.12, 0.89}), luminosities);
}
