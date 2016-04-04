/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../Application.h"
#include "Presentation_Mock.h"
#include "Brightness_Mock.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>


class Application_Test:
    public testing::Test
{
public:
  testing::StrictMock<BrightnessMock> brightness{};
  testing::StrictMock<PresentationMock> presentation{};
  Application testee{brightness, presentation};

};


TEST_F(Application_Test, the_brightness_is_read_when_a_timout_occurs)
{
  EXPECT_CALL(brightness, value()).WillOnce(testing::Return(0.12));
  EXPECT_CALL(presentation, brightness(0.12));

  testee.timeout();
}
