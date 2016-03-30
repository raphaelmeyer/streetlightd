/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Application.h"
#include "Presentation_Mock.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>


class Application_Test:
    public testing::Test
{
public:
  testing::StrictMock<PresentationMock> presentation{};
  Application testee{presentation};

};


TEST_F(Application_Test, an_update_on_the_brightness_is_directly_forwarded)
{
  EXPECT_CALL(presentation, brightness(0.12));

  testee.brightness(0.12);
}

