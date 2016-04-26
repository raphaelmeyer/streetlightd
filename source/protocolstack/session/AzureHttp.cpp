/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "AzureHttp.h"

#include "http/Transfer.h"

#include <Poco/Exception.h>
#include <Poco/Net/Context.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Path.h>
#include <Poco/URI.h>

//TODO poll server

AzureHttp::AzureHttp()
{
}

void AzureHttp::connect()
{
  sender = std::unique_ptr<http::Session>(new http::Session(Poco::URI{uriPost}, tokenFactory));
  receiver = std::unique_ptr<http::Session>(new http::Session(Poco::URI{uriGet}, tokenFactory));
}

void AzureHttp::send(const presentation::Message &message)
{
  sender->post(message.asString());

  const auto response = receiver->get();
  if (response != std::string{}) {
    listener(response);
  }
}

void AzureHttp::setConfiguration(const SessionConfiguration &value)
{
  uriPost = "https://" + value.host + "/devices/" + value.user + "/messages/events?api-version=2016-02-03";
  uriGet = "https://" + value.host + "/devices/" + value.user + "/messages/devicebound?api-version=2016-02-03";
  tokenFactory = SasTokenFactory{value.password, value.host + "/devices/" + value.user};
}

void AzureHttp::close()
{
  receiver.release();
  sender.release();
}

void AzureHttp::setMessageCallback(Session::Callback function)
{
  listener = function;
}

