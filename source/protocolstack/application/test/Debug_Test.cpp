/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../Debug.h"
#include "../message/Incoming.h"
#include "../message/Outgoing.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>


class Debug_Test:
    public testing::Test
{
public:
  typedef std::vector<message::Outgoing> vm;

  void SetUp() override
  {
    testee.setSender([this](const message::Outgoing &message){
      sender.push_back(message);
    });
  }

  std::stringstream output{};
  Debug testee{output};
  vm sender{};
};


TEST_F(Debug_Test, send_message_on_timeout)
{
  testee.timeout();

  ASSERT_EQ(1, sender.size());
}

TEST_F(Debug_Test, outgoing_message_contains_a_counter_in_the_info)
{
  testee.timeout();
  testee.timeout();
  testee.timeout();

  ASSERT_EQ("debug message number 1", sender[0].info());
  ASSERT_EQ("debug message number 2", sender[1].info());
  ASSERT_EQ("debug message number 3", sender[2].info());
}

TEST_F(Debug_Test, print_the_outgoing_message)
{
  testee.timeout();

  ASSERT_EQ("message::Outgoing(info=\"debug message number 1\")\n", output.str());
}

TEST_F(Debug_Test, print_the_incoming_message)
{
  message::Incoming message{};

  testee.received(message);

  ASSERT_EQ("message::Incoming()\n", output.str());
}
