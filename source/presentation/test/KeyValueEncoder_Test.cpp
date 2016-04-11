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

class KeyValueEncoder_Test:
    public testing::Test
{
public:
  typedef std::vector<std::string> vs;

  void SetUp() override
  {
    testee.setListener([this](const std::string &message){
      messages.push_back(message);
    });
  }

  KeyValueEncoder testee{};
  vs messages;

};


TEST_F(KeyValueEncoder_Test, encode_brightness)
{
  testee.brightness(0.78);

  ASSERT_EQ(vs{"brightness 0.78\n"}, messages);
}
