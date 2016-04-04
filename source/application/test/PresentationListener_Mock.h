/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef PRESENTATIONLISTENER_MOCK_H
#define PRESENTATIONLISTENER_MOCK_H

#include "../PresentationListener.h"

#include <gmock/gmock.h>

class PresentationListenerMock :
    public PresentationListener
{
public:
  MOCK_METHOD1(luminosity, void(double));

};

#endif
