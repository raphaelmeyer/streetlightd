/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Visitor_Mock.h"

#include "../Incoming.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>

class message_Incoming_Test :
    public testing::Test
{
public:
  message::Incoming testee{};

};

TEST_F(message_Incoming_Test, can_print_message_)
{
  std::stringstream output{};
  testee.luminosity = 0.42;
  testee.warning = "hello world";

  output << testee;

  ASSERT_EQ("message::Incoming(luminosity=\"0.420000\" warning=\"hello world\")", output.str());
}

TEST_F(message_Incoming_Test, visit_all_values)
{
  const VisitorMock::VisitDouble expectedDoubles = {
    {message::Property::Luminosity, &testee.luminosity}
  };
  const VisitorMock::VisitString expectedStrings = {
    {message::Property::Warning, &testee.warning}
  };
  testing::StrictMock<VisitorMock> visitor;

  testee.accept(visitor);

  ASSERT_EQ(expectedDoubles, visitor.visitDouble);
  ASSERT_EQ(expectedStrings, visitor.visitString);
}
