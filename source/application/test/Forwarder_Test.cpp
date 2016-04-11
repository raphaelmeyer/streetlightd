/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../Forwarder.h"
#include "Presentation_Mock.h"
#include "Sensor_Mock.h"
#include "Actor_Mock.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>


class Forwarder_Test:
    public testing::Test
{
public:
  testing::StrictMock<SensorMock> brightness{};
  testing::StrictMock<ActorMock> luminosity{};
  testing::StrictMock<PresentationMock> presentation{};
  Forwarder testee{brightness, luminosity, presentation};

};


TEST_F(Forwarder_Test, the_brightness_is_read_when_a_timout_occurs)
{
  EXPECT_CALL(brightness, get()).WillOnce(testing::Return(0.12));
  EXPECT_CALL(presentation, brightness(0.12));

  testee.timeout();
}

TEST_F(Forwarder_Test, writes_the_luminosity_when_received_a_new_value)
{
  EXPECT_CALL(luminosity, set(0.45));

  testee.luminosity(0.45);
}
