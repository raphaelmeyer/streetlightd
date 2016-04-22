/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../Outgoing.h"

#include <gtest/gtest.h>
#include <sstream>

class message_Outgoing_Test :
    public testing::Test
{
public:
  std::stringstream output{};
  message::Outgoing message{};

};

TEST_F(message_Outgoing_Test, print_empty_message)
{
  output << message;

  ASSERT_EQ("message::Outgoing()", output.str());
}

TEST_F(message_Outgoing_Test, print_the_brightness)
{
  message.brightness = 0.42;

  output << message;

  ASSERT_EQ("message::Outgoing(brightness=\"0.420000\")", output.str());
}

TEST_F(message_Outgoing_Test, print_the_moisture)
{
  message.moisture = 0.12345;

  output << message;

  ASSERT_EQ("message::Outgoing(moisture=\"0.123450\")", output.str());
}

TEST_F(message_Outgoing_Test, print_the_info)
{
  message.info = "hello world";

  output << message;

  ASSERT_EQ("message::Outgoing(info=\"hello world\")", output.str());
}

TEST_F(message_Outgoing_Test, print_2_values)
{
  message.brightness = 0.42;
  message.info = "hello world";

  output << message;

  ASSERT_EQ("message::Outgoing(brightness=\"0.420000\" info=\"hello world\")", output.str());
}
