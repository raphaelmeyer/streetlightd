/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "StackFactory.h"

StackFactory::StackFactory(Factory<Application *> &_application, Factory<presentation::EncoderAndDecoder> &_presentation, Factory<Session *> &_session) :
  applicationFactory{_application},
  presentationFactory{_presentation},
  sessionFactory{_session}
{
}

static void connect(ProtocolStack &stack)
{
  stack.application->setSender([&stack](const message::Outgoing &message){
    const auto encoded = stack.encoder(message);
    stack.session->send(encoded);
  });

  stack.session->setMessageCallback([&stack](const std::string &message){
    const auto decoded = stack.decoder(message);
    stack.application->received(decoded);
  });
}

ProtocolStack StackFactory::produce(const StackConfiguration &configuration)
{
  //TODO cleanup
  auto application = applicationFactory.produce(configuration.application);
  auto presentation = presentationFactory.produce(configuration.presentation);
  auto session = sessionFactory.produce(configuration.session);

  ProtocolStack stack;
  stack.session = std::unique_ptr<Session>{session};
  stack.encoder = presentation.first;
  stack.decoder = presentation.second;
  std::unique_ptr<Application> appptr{application};
  stack.application = std::unique_ptr<ActiveApplication>{new ActiveApplication(std::move(appptr))};

  connect(stack);
  return stack;
}
