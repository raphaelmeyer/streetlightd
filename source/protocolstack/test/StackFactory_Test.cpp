/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */


//TODO implement tests

//TEST_F(CommandLineParser_Test, create_specified_application)
//{
//  ApplicationMock app;
//  EXPECT_CALL(applicationFactory, produce("theApplication"))
//      .WillOnce(testing::Return(&app));

//  const auto result = testee.parse({"--application=theApplication", "-px", "-sx"});

//  ASSERT_EQ(&app, result.application);
//}

//TEST_F(CommandLineParser_Test, create_specified_presentation)
//{
//  Presentation::Encoder encoder{[](const Outgoing::Message&){return "test";}};
//  Presentation::Decoder decoder{[](const std::string&){return Incoming::Message{};}};
//  EXPECT_CALL(presentationFactory, produce("thePresentation"))
//      .WillOnce(testing::Return(Presentation::EncoderAndDecoder{encoder, decoder}));

//  const auto result = testee.parse({"--presentation=thePresentation", "-ax", "-sx"});

//  ASSERT_EQ("test", result.presentation.first({}));
//}

//TEST_F(CommandLineParser_Test, create_specified_session)
//{
//  SessionMock session;
//  EXPECT_CALL(sessionFactory, produce("theSession"))
//      .WillOnce(testing::Return(&session));

//  const auto result = testee.parse({"--session=theSession", "-ax", "-px"});

//  ASSERT_EQ(&session, result.session);
//}

