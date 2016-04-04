/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef ACTOR_MOCK_H
#define ACTOR_MOCK_H

#include "../Actor.h"

#include <gmock/gmock.h>

class ActorMock :
    public Actor
{
public:
  MOCK_METHOD1(set, void(double));

};

#endif
