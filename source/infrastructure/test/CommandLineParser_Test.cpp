/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../CommandLineParser.h"
#include "Factory_Mock.h"
#include <protocolstack/application/test/Application_Mock.h>
#include <protocolstack/session/test/Session_Mock.h>

#include <protocolstack/application/Application.h>
#include <protocolstack/presentation/Presentation.h>
#include <protocolstack/session/Session.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <string>

class CommandLineParser_Test:
    public testing::Test
{
public:
  testing::NiceMock<FactoryMock<Application*>> applicationFactory{};
  testing::NiceMock<FactoryMock<Presentation::EncoderAndDecoder>> presentationFactory{};
  testing::NiceMock<FactoryMock<Session*>> sessionFactory{};
  std::stringstream output{};
  CommandLineParser testee{output, applicationFactory, presentationFactory, sessionFactory};

  const std::string DefaultHelp {
    "usage: \n"
    "-h, --help                                       print this help\n"
    "-a<application>, --application=<application>     <application>:\n"
    "-p<presentation>, --presentation=<presentation>  <presentation>:\n"
    "-s<session>, --session=<session>                 <session>:\n"
    "--address=<address>                              address to connect to\n"
    "--credential=<credential>                        credentials for connection\n"
  };

};

TEST_F(CommandLineParser_Test, output_is_not_valid_when_provided_invalid_arguments)
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

//TEST_F(CommandLineParser_Test, does_not_print_help_for_correct_number_of_arguments)
//{
//  testee.parse({"my name", "application", "presentation", "session"});

//  ASSERT_EQ("", output.str());
//}

TEST_F(CommandLineParser_Test, output_is_valid_when_provided_with_valid_arguments)
{
  ApplicationMock app;
  ON_CALL(applicationFactory, produce("A"))
      .WillByDefault(testing::Return(&app));
  Presentation::Encoder encoder{[](const Outgoing::Message&){return "test";}};
  Presentation::Decoder decoder{[](const std::string&){return Incoming::Message{};}};
  ON_CALL(presentationFactory, produce("P"))
      .WillByDefault(testing::Return(Presentation::EncoderAndDecoder{encoder, decoder}));
  SessionMock session;
  ON_CALL(sessionFactory, produce("S"))
      .WillByDefault(testing::Return(&session));

  const auto result = testee.parse({"--application=A", "--presentation=P", "--session=S"});

  ASSERT_TRUE(output.str().empty());
  ASSERT_TRUE(result);
}

TEST_F(CommandLineParser_Test, show_available_applications_in_help)
{
  ON_CALL(applicationFactory, workers())
      .WillByDefault(testing::Return(std::set<std::string>{"app1", "app2", "app3"}));

  testee.parse({});

  const std::string message{output.str()};
  const bool found = message.find("<application>: app1 app2 app3") != std::string::npos;
  ASSERT_TRUE(found) << "got: " << std::endl << message;
}

TEST_F(CommandLineParser_Test, show_available_presentations_in_help)
{
  ON_CALL(presentationFactory, workers())
      .WillByDefault(testing::Return(std::set<std::string>{"pres1", "pres2"}));

  testee.parse({});

  const std::string message{output.str()};
  const bool found = message.find("<presentation>: pres1 pres2") != std::string::npos;
  ASSERT_TRUE(found) << "got: " << std::endl << message;
}

TEST_F(CommandLineParser_Test, show_available_sessions_in_help)
{
  ON_CALL(sessionFactory, workers())
      .WillByDefault(testing::Return(std::set<std::string>{"one", "two"}));

  testee.parse({});

  const std::string message{output.str()};
  const bool found = message.find("<session>: one two") != std::string::npos;
  ASSERT_TRUE(found) << "got: " << std::endl << message;
}

TEST_F(CommandLineParser_Test, create_specified_application)
{
  ApplicationMock app;
  EXPECT_CALL(applicationFactory, produce("theApplication"))
      .WillOnce(testing::Return(&app));

  const auto result = testee.parse({"--application=theApplication", "-px", "-sx"});

  ASSERT_EQ(&app, result.application);
}

TEST_F(CommandLineParser_Test, create_specified_presentation)
{
  Presentation::Encoder encoder{[](const Outgoing::Message&){return "test";}};
  Presentation::Decoder decoder{[](const std::string&){return Incoming::Message{};}};
  EXPECT_CALL(presentationFactory, produce("thePresentation"))
      .WillOnce(testing::Return(Presentation::EncoderAndDecoder{encoder, decoder}));

  const auto result = testee.parse({"--presentation=thePresentation", "-ax", "-sx"});

  ASSERT_EQ("test", result.presentation.first({}));
}

TEST_F(CommandLineParser_Test, create_specified_session)
{
  SessionMock session;
  EXPECT_CALL(sessionFactory, produce("theSession"))
      .WillOnce(testing::Return(&session));

  const auto result = testee.parse({"--session=theSession", "-ax", "-px"});

  ASSERT_EQ(&session, result.session);
}
