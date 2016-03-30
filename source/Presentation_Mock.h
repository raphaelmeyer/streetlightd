/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef PRESENTATION_MOCK
#define PRESENTATION_MOCK

#include "Presentation.h"

#include <gmock/gmock.h>

class PresentationMock :
    public Presentation
{
public:
  MOCK_METHOD1(brightness, void(double));

};

#endif

