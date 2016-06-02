/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Factory.h"

#include "AzureAmqp.h"
#include "AzureAmqpWs.h"
#include "AzureHttp.h"
#include "mqtt/Azure.h"
#include "mqtt/Simple.h"
#include "mqtt/Client.h"
#include "Null.h"

namespace session
{

/**
 * Azure connection via MQTT through mosquitto.
 */
class AzureMqtt :
    public mqtt::Client
{
public:
  AzureMqtt() :
    mqtt::Client{new mqtt::Azure()}
  {
  }
};

/**
 * MQTT connector usable for unencrypted connections.
 */
class SimpleMqtt :
    public mqtt::Client
{
public:
  SimpleMqtt() :
    mqtt::Client{new mqtt::Simple()}
  {
  }
};

Factory<Session*> factory()
{
  Factory<Session*> factory;
  factory.add("none", []{return new session::Null();});
  factory.add("azure-amqp", []{return new AzureAmqp();});
  factory.add("azure-amqp-ws", []{return new AzureAmqpWs();});
  factory.add("azure-http", []{return new AzureHttp();});
  factory.add("azure-mqtt", []{return new AzureMqtt();});
  factory.add("simple-mqtt", []{return new SimpleMqtt();});
  return factory;
}

}
