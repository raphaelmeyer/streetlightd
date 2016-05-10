/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Client.h"

#include "util.h"

namespace mqtt
{

Client::Client(Configuration *_configuration) :
  mosqpp::mosquittopp{},
  configuration{_configuration}
{
  throwIfError("lib_init", mosqpp::lib_init());
}

Client::~Client()
{
  throwIfError("lib_cleanup", mosqpp::lib_cleanup());
}

void Client::setConfiguration(const session::Configuration &value)
{
  configuration->setConfiguration(value);

  reinitialise(configuration->deviceId().c_str(), true);
}

void Client::connect()
{
  configuration->configure(*this);

  throwIfError("connect", mosqpp::mosquittopp::connect(configuration->address().c_str(), configuration->port()));

  throwIfError("loop_start", loop_start());
}

void Client::on_connect(int)
{
  const auto result = subscribe(nullptr, configuration->receiveTopic().c_str(), configuration->qos());
  throwIfError("subscribe", result);
}

void Client::close()
{
  const auto disconnectResult = disconnect();
  throwIfError("disconnect", disconnectResult);

  const auto stopResult = loop_stop();
  throwIfError("loop_stop", stopResult);
}

void Client::send(const presentation::Message &message)
{
  const auto result = publish(nullptr, configuration->sendTopic().c_str(), message.asBinary().size(), message.asBinary().data(), configuration->qos());
  throwIfError("publish", result);
}

void Client::on_message(const mosquitto_message *message)
{
  const presentation::Message payload{message->payload, static_cast<size_t>(message->payloadlen)};
  listener(payload);
}

void Client::on_error()
{
  throw std::runtime_error("undefined error in MQTT");
}

void Client::setMessageCallback(Callback function)
{
  listener = function;
}

}
