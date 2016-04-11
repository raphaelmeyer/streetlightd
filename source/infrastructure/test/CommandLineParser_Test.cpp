/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../CommandLineParser.h"
#include "Factory_Mock.h"
#include "../../application/test/Application_Mock.h"
#include "../../presentation/test/Session_Mock.h"

#include <application/Application.h>
#include <application/Presentation.h>
#include <presentation/Session.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>

class CommandLineParser_Test:
    public testing::Test
{
public:
  testing::NiceMock<FactoryMock<Application*>> applicationFactory{};
  testing::NiceMock<FactoryMock<Presentation::EncoderAndDecoder>> presentationFactory{};
  testing::NiceMock<FactoryMock<Session*>> sessionFactory{};
  std::stringstream output{};
  CommandLineParser testee{output, applicationFactory, presentationFactory, sessionFactory};

};

TEST_F(CommandLineParser_Test, output_is_not_valid_when_provided_invalid_arguments)
{
  const auto result = testee.parse({});

  ASSERT_FALSE(result);
}

TEST_F(CommandLineParser_Test, show_help_by_default)
{
  const std::string expected{
      "expecting the following arguments: <application> <presentation> <session>\n"
      "  application:\n"
      "  presentation:\n"
      "  session:\n"
  };

  testee.parse({});

  ASSERT_EQ(expected, output.str());
}

TEST_F(CommandLineParser_Test, does_not_print_help_for_correct_number_of_arguments)
{
  testee.parse({"my name", "application", "presentation", "session"});

  ASSERT_EQ("", output.str());
}

TEST_F(CommandLineParser_Test, output_is_valid_when_provided_with_valid_arguments)
{
  ApplicationMock app;
  ON_CALL(applicationFactory, produce("application"))
      .WillByDefault(testing::Return(&app));
  Presentation::Encoder encoder{[](double){return "test";}};
  Presentation::Decoder decoder{[](const std::string&){return Incoming::Message{};}};
  ON_CALL(presentationFactory, produce("presentation"))
      .WillByDefault(testing::Return(Presentation::EncoderAndDecoder{encoder, decoder}));
  SessionMock session;
  ON_CALL(sessionFactory, produce("session"))
      .WillByDefault(testing::Return(&session));

  const auto result = testee.parse({"my name", "application", "presentation", "session"});

  ASSERT_TRUE(result);
}

TEST_F(CommandLineParser_Test, show_available_applications_in_help)
{
  ON_CALL(applicationFactory, workers())
      .WillByDefault(testing::Return(std::set<std::string>{"app1", "app2", "app3"}));
  const std::string expected{
      "expecting the following arguments: <application> <presentation> <session>\n"
      "  application: app1 app2 app3\n"
      "  presentation:\n"
      "  session:\n"
  };

  testee.parse({});

  ASSERT_EQ(expected, output.str());
}

TEST_F(CommandLineParser_Test, show_available_presentations_in_help)
{
  ON_CALL(presentationFactory, workers())
      .WillByDefault(testing::Return(std::set<std::string>{"pres1", "pres2"}));
  const std::string expected{
      "expecting the following arguments: <application> <presentation> <session>\n"
      "  application:\n"
      "  presentation: pres1 pres2\n"
      "  session:\n"
  };

  testee.parse({});

  ASSERT_EQ(expected, output.str());
}

TEST_F(CommandLineParser_Test, show_available_sessions_in_help)
{
  ON_CALL(sessionFactory, workers())
      .WillByDefault(testing::Return(std::set<std::string>{"one", "two"}));
  const std::string expected{
      "expecting the following arguments: <application> <presentation> <session>\n"
      "  application:\n"
      "  presentation:\n"
      "  session: one two\n"
  };

  testee.parse({});

  ASSERT_EQ(expected, output.str());
}

TEST_F(CommandLineParser_Test, create_specified_application)
{
  ApplicationMock app;
  EXPECT_CALL(applicationFactory, produce("the application"))
      .WillOnce(testing::Return(&app));

  const auto result = testee.parse({"", "the application", "", ""});

  ASSERT_EQ(&app, result.application);
}

TEST_F(CommandLineParser_Test, create_specified_presentation)
{
  Presentation::Encoder encoder{[](double){return "test";}};
  Presentation::Decoder decoder{[](const std::string&){return Incoming::Message{};}};
  EXPECT_CALL(presentationFactory, produce("the presentation"))
      .WillOnce(testing::Return(Presentation::EncoderAndDecoder{encoder, decoder}));

  const auto result = testee.parse({"", "", "the presentation", ""});

  ASSERT_EQ("test", result.presentation.first(0));
}

TEST_F(CommandLineParser_Test, create_specified_session)
{
  SessionMock session;
  EXPECT_CALL(sessionFactory, produce("the session"))
      .WillOnce(testing::Return(&session));

  const auto result = testee.parse({"", "", "", "the session"});

  ASSERT_EQ(&session, result.session);
}
