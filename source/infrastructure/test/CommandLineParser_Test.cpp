/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../CommandLineParser.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <set>
#include <string>

class CommandLineParser_Test:
    public testing::Test
{
public:
  std::stringstream output{};
  CommandLineParser testee{output};

  const std::string DefaultHelp {
    "usage: \n"
    "-h, --help                                       print this help\n"
    "-a<application>, --application=<application>     <application>:\n"
    "-p<presentation>, --presentation=<presentation>  <presentation>:\n"
    "-s<session>, --session=<session>                 <session>:\n"
    "--host=<host>                                    host to connect to\n"
    "--user=<user>                                    user of connection\n"
    "--password=<password>                            password for connection\n"
    "--external-timer                                 trigger updates via DBus\n"
  };

};

TEST_F(CommandLineParser_Test, output_is_not_valid_when_not_provided_all_arguments)
{
  const auto result = testee.parse({});

  ASSERT_FALSE(result);
}

TEST_F(CommandLineParser_Test, show_help_when_requested)
{
  testee.parse({"--help"});

  ASSERT_EQ(DefaultHelp, output.str());
}

TEST_F(CommandLineParser_Test, show_help_when_missing_required_arguments)
{
  testee.parse({});

  ASSERT_EQ(DefaultHelp, output.str());
}

TEST_F(CommandLineParser_Test, show_help_for_missing_option_argument)
{
  testee.parse({"--application", "-px", "-sx"});

  ASSERT_EQ(DefaultHelp, output.str());
}

TEST_F(CommandLineParser_Test, show_help_if_unknown_option_is_provided)
{
  testee.parse({"-ax", "-px", "-sx", "--unknown"});

  ASSERT_EQ(DefaultHelp, output.str());
}

TEST_F(CommandLineParser_Test, output_is_valid_when_provided_with_valid_arguments)
{
  testee.addApplications({"A"});
  testee.addPresentations({"P"});
  testee.addSessions({"S"});

  const auto result = testee.parse({"--application=A", "--presentation=P", "--session=S"});

  ASSERT_TRUE(output.str().empty());
  ASSERT_TRUE(result);
}

TEST_F(CommandLineParser_Test, output_is_not_valid_when_provided_invalid_arguments)
{
  testee.addApplications({"A"});
  testee.addPresentations({"P"});
  testee.addSessions({"S"});

  const auto result = testee.parse({"--application=X", "--presentation=P", "--session=S"});

  ASSERT_FALSE(result);
}

TEST_F(CommandLineParser_Test, show_available_applications_in_help)
{
  testee.addApplications({"app1", "app2", "app3"});

  testee.parse({});

  const std::string message{output.str()};
  const bool found = message.find("<application>: app1 app2 app3") != std::string::npos;
  ASSERT_TRUE(found) << "got: " << std::endl << message;
}

TEST_F(CommandLineParser_Test, show_available_presentations_in_help)
{
  testee.addPresentations({"pres1", "pres2"});

  testee.parse({});

  const std::string message{output.str()};
  const bool found = message.find("<presentation>: pres1 pres2") != std::string::npos;
  ASSERT_TRUE(found) << "got: " << std::endl << message;
}

TEST_F(CommandLineParser_Test, show_available_sessions_in_help)
{
  testee.addSessions({"one", "two"});

  testee.parse({});

  const std::string message{output.str()};
  const bool found = message.find("<session>: one two") != std::string::npos;
  ASSERT_TRUE(found) << "got: " << std::endl << message;
}

TEST_F(CommandLineParser_Test, return_the_specified_application)
{
  testee.addApplications({"theApplication"});
  testee.addPresentations({"x"});
  testee.addSessions({"x"});

  const auto result = testee.parse({"--application=theApplication", "-px", "-sx"});

  ASSERT_EQ("theApplication", result.application);
}

TEST_F(CommandLineParser_Test, return_the_specified_presentation)
{
  testee.addPresentations({"thePresentation"});
  testee.addApplications({"x"});
  testee.addSessions({"x"});

  const auto result = testee.parse({"--presentation=thePresentation", "-ax", "-sx"});

  ASSERT_EQ("thePresentation", result.presentation);
}

TEST_F(CommandLineParser_Test, return_the_specified_session)
{
  testee.addSessions({"theSession"});
  testee.addPresentations({"x"});
  testee.addApplications({"x"});

  const auto result = testee.parse({"--session=theSession", "-ax", "-px"});

  ASSERT_EQ("theSession", result.session);
}

TEST_F(CommandLineParser_Test, can_specify_the_host)
{
  testee.addSessions({"x"});
  testee.addPresentations({"x"});
  testee.addApplications({"x"});

  const auto result = testee.parse({"--host=someAddress", "-ax", "-px", "-sx"});

  ASSERT_EQ("someAddress", result.host);
}

TEST_F(CommandLineParser_Test, can_specify_the_user)
{
  testee.addSessions({"x"});
  testee.addPresentations({"x"});
  testee.addApplications({"x"});

  const auto result = testee.parse({"--user=someUser", "-ax", "-px", "-sx"});

  ASSERT_EQ("someUser", result.user);
}

TEST_F(CommandLineParser_Test, can_specify_password)
{
  testee.addSessions({"x"});
  testee.addPresentations({"x"});
  testee.addApplications({"x"});

  const auto result = testee.parse({"--password=mySecret", "-ax", "-px", "-sx"});

  ASSERT_EQ("mySecret", result.password);
}

TEST_F(CommandLineParser_Test, do_not_use_external_timer_by_default)
{
  testee.addSessions({"x"});
  testee.addPresentations({"x"});
  testee.addApplications({"x"});

  const auto result = testee.parse({"-ax", "-px", "-sx"});

  ASSERT_FALSE(result.externalTimer);
}

TEST_F(CommandLineParser_Test, can_specify_to_use_external_timer)
{
  testee.addSessions({"x"});
  testee.addPresentations({"x"});
  testee.addApplications({"x"});

  const auto result = testee.parse({"--external-timer", "-ax", "-px", "-sx"});

  ASSERT_TRUE(result.externalTimer);
}
