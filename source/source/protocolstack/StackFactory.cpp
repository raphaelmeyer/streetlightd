/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "StackFactory.h"

#include "application/Factory.h"
#include "session/Factory.h"
#include "presentation/Factory.h"

StackFactory::StackFactory() :
  applicationFactory{application::factory()},
  presentationFactory{presentation::factory()},
  sessionFactory{session::factory()}
{
}

std::set<std::string> StackFactory::applications() const
{
  return applicationFactory.workers();
}

std::set<std::string> StackFactory::presentations() const
{
  return presentationFactory.workers();
}

std::set<std::string> StackFactory::sessions() const
{
  return sessionFactory.workers();
}

static void connect(ProtocolStack &stack)
{
  stack.application->setSender([&stack](const message::Outgoing &message){
    const auto encoded = stack.presentation->encode(message);
    stack.session->send(encoded);
  });

  stack.session->setMessageCallback([&stack](const presentation::Message &message){
    const auto decoded = stack.presentation->decode(message);
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
  stack.presentation = std::unique_ptr<Presentation>{presentation};
  std::unique_ptr<Application> appptr{application};
  stack.application = std::unique_ptr<ActiveApplication>{new ActiveApplication(std::move(appptr))};

  connect(stack);
  return stack;
}
