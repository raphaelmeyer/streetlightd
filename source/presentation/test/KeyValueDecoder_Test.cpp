/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../KeyValueDecoder.h"

#include <application/test/PresentationListener_Mock.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>


class KeyValueDecoder_Test:
    public testing::Test
{
public:
  testing::StrictMock<PresentationListenerMock> listener{};
  KeyValueDecoder testee{listener};

};

TEST_F(KeyValueDecoder_Test, does_nothing_for_an_empty_message)
{
  EXPECT_CALL(listener, luminosity(testing::_)).Times(0);

  testee.decode("");
  testee.decode("\n");
  testee.decode("\n\n");
  testee.decode("  ");
  testee.decode("  \n");
}

TEST_F(KeyValueDecoder_Test, decode_luminosity)
{
  EXPECT_CALL(listener, luminosity(0.41));

  testee.decode("luminosity 0.41\n");
}

TEST_F(KeyValueDecoder_Test, does_not_call_luminosity_for_different_key)
{
  EXPECT_CALL(listener, luminosity(testing::_)).Times(0);

  testee.decode("a-different-key 0.23\n");
}

TEST_F(KeyValueDecoder_Test, calls_method_as_often_as_the_key_occurs)
{
  EXPECT_CALL(listener, luminosity(0));
  EXPECT_CALL(listener, luminosity(0.12));
  EXPECT_CALL(listener, luminosity(0.89));

  testee.decode("luminosity 0\nluminosity 0.12\nluminosity 0.89\n");
}
