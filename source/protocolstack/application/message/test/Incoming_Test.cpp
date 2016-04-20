/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../Incoming.h"

#include <gtest/gtest.h>
#include <sstream>

class message_Incoming_Test :
    public testing::Test
{
public:
  std::stringstream output{};
  message::Incoming message{};

};

TEST_F(message_Incoming_Test, print_empty_message)
{
  output << message;

  ASSERT_EQ("message::Incoming()", output.str());
}

TEST_F(message_Incoming_Test, print_the_luminosity)
{
  message.luminosity = 0.42;

  output << message;

  ASSERT_EQ("message::Incoming(luminosity=\"0.420000\")", output.str());
}

TEST_F(message_Incoming_Test, print_the_warning)
{
  message.warning = "hello world";

  output << message;

  ASSERT_EQ("message::Incoming(warning=\"hello world\")", output.str());
}

TEST_F(message_Incoming_Test, print_2_values)
{
  message.luminosity = 0.42;
  message.warning = "hello world";

  output << message;

  ASSERT_EQ("message::Incoming(luminosity=\"0.420000\" warning=\"hello world\")", output.str());
}
