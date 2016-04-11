/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef APPLICATION_MOCK_H
#define APPLICATION_MOCK_H

#include <protocolstack/application/Application.h>

#include <gmock/gmock.h>

class ApplicationMock :
    public Application
{
public:
  MOCK_METHOD0(timeout, void());
  MOCK_METHOD1(received, void(const Incoming::Message &));

  MOCK_METHOD1(setBrightnessSensor, void(Sensor));
  MOCK_METHOD1(setLuminosityActor, void(Actor));
  MOCK_METHOD1(setSender, void(Sender));

};

#endif
