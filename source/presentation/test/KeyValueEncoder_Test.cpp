/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../KeyValueEncoder.h"
#include "Session_Mock.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>


class KeyValueEncoder_Test:
    public testing::Test
{
public:
  testing::StrictMock<SessionMock> session{};
  KeyValueEncoder testee{session};

};


TEST_F(KeyValueEncoder_Test, encode_brightness)
{
  EXPECT_CALL(session, send("brightness 0.78\n"));

  testee.brightness(0.78);
}
