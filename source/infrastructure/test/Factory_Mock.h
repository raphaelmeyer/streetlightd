/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef FACTORY_MOCK_H
#define FACTORY_MOCK_H

#include "../Factory.h"

#include <gmock/gmock.h>

template<class T>
class FactoryMock :
    public Factory<T>
{
public:
  MOCK_CONST_METHOD0(workers, std::set<std::string>());
  MOCK_CONST_METHOD1_T(produce, T(const std::string &product));

};


#endif
