/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Visitor_Mock.h"

#include "../Outgoing.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>

class message_Outgoing_Test :
    public testing::Test
{
public:
  message::Outgoing testee{};

};

TEST_F(message_Outgoing_Test, can_print_message)
{
  std::stringstream output{};
  testee.brightness = 0.42;
  testee.info = "hello world";

  output << testee;

  ASSERT_EQ("message::Outgoing(brightness=\"0.420000\" info=\"hello world\")", output.str());
}

TEST_F(message_Outgoing_Test, visit_header_and_footer)
{
  testing::StrictMock<VisitorMock> visitor;

  EXPECT_CALL(visitor, outgoingHeader());
  EXPECT_CALL(visitor, outgoingFooter());

  testee.accept(visitor);
}

TEST_F(message_Outgoing_Test, visit_all_values)
{
  const VisitorMock::VisitDouble expectedDoubles = {
    {message::Property::Brightness, &testee.brightness},
    {message::Property::Moisture, &testee.moisture},
    {message::Property::Proximity, &testee.proximity}
  };
  const VisitorMock::VisitString expectedStrings = {
    {message::Property::Info, &testee.info}
  };
  testing::NiceMock<VisitorMock> visitor;

  testee.accept(visitor);

  ASSERT_EQ(expectedDoubles, visitor.visitDouble);
  ASSERT_EQ(expectedStrings, visitor.visitString);
}
