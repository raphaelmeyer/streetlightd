/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../Offline.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>


class Offline_Test:
    public testing::Test
{
public:
  typedef std::vector<double> vd;

  void SetUp() override
  {
    testee.setBrightnessSensor([this]{
      return brightness;
    });
    testee.setLuminosityActor([this](double value){
      luminosity.push_back(value);
    });
  }

  Offline testee{};

  double brightness{-1};
  vd luminosity{};

};

TEST_F(Offline_Test, ignores_incoming_messages)
{
  message::Incoming message;
  message.luminosity = 0.42;
  message.warning = "hello world";

  testee.received(message);

  ASSERT_EQ(0, luminosity.size());
}

TEST_F(Offline_Test, sets_the_luminosity_when_a_timeout_occurs)
{
  testee.timeout();

  ASSERT_EQ(1, luminosity.size());
}

TEST_F(Offline_Test, sets_the_luminosity_to_100_per_cent_for_a_brightness_lower_than_25_per_cent)
{
  brightness = 0.0;
  testee.timeout();

  brightness = 0.1;
  testee.timeout();

  brightness = 0.2;
  testee.timeout();

  ASSERT_EQ(vd({1, 1, 1}), luminosity);
}

TEST_F(Offline_Test, sets_the_luminosity_to_0_per_cent_for_a_brightness_higher_than_25_per_cent)
{
  brightness = 0.3;
  testee.timeout();

  brightness = 0.4;
  testee.timeout();

  brightness = 0.5;
  testee.timeout();

  brightness = 0.6;
  testee.timeout();

  brightness = 0.7;
  testee.timeout();

  brightness = 0.8;
  testee.timeout();

  brightness = 0.9;
  testee.timeout();

  brightness = 1.0;
  testee.timeout();

  ASSERT_EQ(vd({0, 0, 0, 0, 0, 0, 0, 0}), luminosity);
}
