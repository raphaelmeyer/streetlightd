/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Mqtt.h"
#include "StreetlightProxy.h"

#include "Application.h"
#include "KeyValueEncoder.h"
#include "Session.h"

#include <dbus-c++/dbus.h>
#include <dbus-c++/api.h>
#include <dbus-c++-1/dbus-c++/dbus.h>

#include <thread>
#include <iostream>

class Brightness :
    public ch::bbv::StreetLight::Brightness_proxy,
    public DBus::IntrospectableProxy,
    public DBus::ObjectProxy
{
public:
  Brightness(SensorListener &_sensorListener, DBus::Connection& connection) :
    DBus::ObjectProxy(connection, "/StreetLight", "ch.bbv.StreetLight.Brightness"),
    sensorListener{_sensorListener}
  {
  }

  void update(const double& value) override
  {
    sensorListener.brightness(value);
  }

private:
   SensorListener &sensorListener;
};

class AzureMqtt :
    public Session
{
public:
  AzureMqtt(Mqtt &_mqtt) :
    mqtt{_mqtt}
  {
  }

  void send(const std::string &message) override
  {
    mqtt.publish(nullptr, topic.c_str(), message.size(), message.c_str(), 2, false);
  }

private:
  Mqtt &mqtt;
  const std::string topic{"devices/Device1/messages/devicebound/test"};

};

int main()
{
  Mqtt mqtt{};
  mqtt.connect("localhost");

  DBus::BusDispatcher dispatcher;
  DBus::default_dispatcher = &dispatcher;
  DBus::Connection connection = DBus::Connection::SessionBus();

  AzureMqtt session{mqtt};
  KeyValueEncoder presentation{session};
  Application application{presentation};

  Brightness brightness(application, connection);

  mqtt.loop_start();
  dispatcher.enter();
  mqtt.loop_stop();

  mqtt.disconnect();

  return 0;
}
