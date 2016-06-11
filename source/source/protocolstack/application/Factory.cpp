/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Factory.h"

#include "Debug.h"
#include "Forwarder.h"
#include "Offline.h"

#include <iostream>

namespace application
{

Factory<Application*> factory()
{
  Factory<Application*> factory;
  factory.add("forwarder", []{return new Forwarder();});
  factory.add("debug", []{return new Debug(std::cout);});
  factory.add("offline", []{return new Offline();});
  return factory;
}

}
