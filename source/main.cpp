/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Mqtt.h"

#include <iostream>

int main()
{
  const std::string topic{"devices/Device1/messages/devicebound/test"};
  const std::string message{"brightness 0.34\n"};

  Mqtt mqtt{};
  mqtt.connect("localhost");
  mqtt.publish(nullptr, topic.c_str(), message.size(), message.c_str(), 2, false);

  while (true) {
    mqtt.loop(1000, 1);
  }

  return 0;
}
