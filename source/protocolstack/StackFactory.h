/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "ProtocolStack.h"

#ifndef STACKFACTORY_H
#define STACKFACTORY_H

#include "../infrastructure/Factory.h"
#include <protocolstack/application/Application.h>
#include <protocolstack/presentation/Presentation.h>
#include <protocolstack/session/Session.h>

class StackConfiguration
{
public:
  std::string application{};
  std::string presentation{};
  std::string session{};

  operator bool() const
  {
    return !application.empty() && !presentation.empty() && !session.empty();
  }
};

class StackFactory
{
public:
  StackFactory(Factory<Application*> &applicationFactory, Factory<Presentation::EncoderAndDecoder> &presentationFactory, Factory<Session*> &sessionFactory);

  ProtocolStack produce(const StackConfiguration &configuration);

private:
  Factory<Application*> &applicationFactory;
  Factory<Presentation::EncoderAndDecoder> &presentationFactory;
  Factory<Session*> &sessionFactory;

};

#endif
