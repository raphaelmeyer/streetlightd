/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Mqtt.h"
#include "StreetlightProxy.h"

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
  Brightness(Mqtt &_mqtt, DBus::Connection& connection) :
    DBus::ObjectProxy(connection, "/StreetLight", "ch.bbv.StreetLight.Brightness"),
    mqtt{_mqtt}
  {
  }

  void update(const double& value) override
  {
    const std::string topic{"devices/Device1/messages/devicebound/test"};
    std::stringstream stream;
    stream << "brightness " << value << std::endl;
    const std::string message{stream.str()};
    mqtt.publish(nullptr, topic.c_str(), message.size(), message.c_str(), 2, false);
  }

private:
   Mqtt &mqtt;
};

int main()
{
  Mqtt mqtt{};
  mqtt.connect("localhost");

  DBus::BusDispatcher dispatcher;
  DBus::default_dispatcher = &dispatcher;
  DBus::Connection connection = DBus::Connection::SessionBus();

  Brightness brightness(mqtt, connection);

  mqtt.loop_start();
  dispatcher.enter();
  mqtt.loop_stop();

  mqtt.disconnect();

  return 0;
}
