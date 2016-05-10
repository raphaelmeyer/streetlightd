/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Factory.h"

#include "AzureAmqp.h"
#include "AzureHttp.h"
#include "AzureMqtt.h"
#include "SimpleMqtt.h"
#include "mqtt/Client.h"
#include "Null.h"

namespace session
{

Factory<Session*> factory()
{
  Factory<Session*> factory;
  factory.add("none", []{return new session::Null();});
  factory.add("azure-amqp", []{return new AzureAmqp();});
  factory.add("azure-http", []{return new AzureHttp();});
  factory.add("azure-mqtt", []{return new mqtt::Client(new AzureMqtt());});
  factory.add("simple-mqtt", []{return new mqtt::Client(new SimpleMqtt());});
  return factory;
}

}
