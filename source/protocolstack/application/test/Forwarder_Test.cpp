/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../Forwarder.h"
#include "../IncomingMessage.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>


class Forwarder_Test:
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
    testee.setListener([this](double brightness){
      listenerBrightness.push_back(brightness);
    });
  }

  Forwarder testee{};

  double brightness{-1};
  vd luminosity{};
  vd listenerBrightness{};

};


TEST_F(Forwarder_Test, the_brightness_is_read_when_a_timout_occurs)
{
  brightness = 0.12;

  testee.timeout();

  ASSERT_EQ(vd{0.12}, listenerBrightness);
}

TEST_F(Forwarder_Test, does_not_write_the_luminosity_when_not_set)
{
  const Incoming::Message message{};

  testee.received(message);

  ASSERT_EQ(vd{}, luminosity);
}

TEST_F(Forwarder_Test, writes_the_luminosity_when_received_a_new_value)
{
  const Incoming::Message message{{Incoming::Type::Luminosity, 0.45}};

  testee.received(message);

  ASSERT_EQ(vd{0.45}, luminosity);
}
