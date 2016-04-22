/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../Forwarder.h"
#include "../message/Incoming.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>


class Forwarder_Test:
    public testing::Test
{
public:
  typedef std::vector<double> vd;
  typedef std::vector<std::string> vs;
  typedef std::vector<message::Outgoing> vm;

  void SetUp() override
  {
    testee.setBrightnessSensor([this]{
      return brightness;
    });
    testee.setMoistureSensor([this]{
      return moisture;
    });
    testee.setLuminosityActor([this](double value){
      luminosity.push_back(value);
    });
    testee.setWarningActor([this](std::string value){
      warning.push_back(value);
    });
    testee.setSender([this](const message::Outgoing &message){
      sender.push_back(message);
    });
  }

  Forwarder testee{};

  double brightness{-1};
  double moisture{-1};
  vd luminosity{};
  vs warning{};
  vm sender{};

};


TEST_F(Forwarder_Test, the_brightness_is_read_when_a_timout_occurs)
{
  brightness = 0.12;

  testee.timeout();

  ASSERT_EQ(0.12, sender[0].brightness());
}

TEST_F(Forwarder_Test, the_moisture_is_read_when_a_timout_occurs)
{
  moisture = 0.12;

  testee.timeout();

  ASSERT_EQ(0.12, sender[0].moisture());
}

TEST_F(Forwarder_Test, does_not_write_anything_when_not_set)
{
  const message::Incoming message{};

  testee.received(message);

  ASSERT_EQ(vd{}, luminosity);
  ASSERT_EQ(vs{}, warning);
}

TEST_F(Forwarder_Test, writes_the_luminosity_when_received_a_new_value)
{
  message::Incoming message;
  message.luminosity = 0.45;

  testee.received(message);

  ASSERT_EQ(vd{0.45}, luminosity);
}

TEST_F(Forwarder_Test, writes_the_warning_when_received_a_new_value)
{
  message::Incoming message;
  message.warning = "hello world";

  testee.received(message);

  ASSERT_EQ(vs{"hello world"}, warning);
}
