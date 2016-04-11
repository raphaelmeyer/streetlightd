/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef APPLICATION_MOCK_H
#define APPLICATION_MOCK_H

#include <application/Application.h>

#include <gmock/gmock.h>

class ApplicationMock :
    public Application
{
public:
  MOCK_METHOD0(timeout, void());
  MOCK_METHOD1(luminosity, void(double));

};

#endif
