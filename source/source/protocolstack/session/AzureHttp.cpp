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

AzureHttp::AzureHttp()
{
}

void AzureHttp::connect()
{
  sender = std::unique_ptr<http::Session>(new http::Session(Poco::URI{uriPost}, tokenFactory));

  Callback callback = listener;
  std::shared_ptr<http::Session> receiverSession = std::shared_ptr<http::Session>(new http::Session(Poco::URI{uriGet}, tokenFactory, [callback](const auto &value){
    callback(value);
  }));
  auto tickHandler = [receiverSession] {
    receiverSession->get();
  };
  receiver = std::unique_ptr<concurrency::Timer>(new concurrency::Timer(tickHandler));
}

void AzureHttp::send(const presentation::Message &message)
{
  sender->post(message.asString());
}

void AzureHttp::setConfiguration(const session::Configuration &value)
{
  uriPost = "https://" + value.host + "/devices/" + value.user + "/messages/events?api-version=2016-02-03";
  uriGet = "https://" + value.host + "/devices/" + value.user + "/messages/devicebound?api-version=2016-02-03";
  tokenFactory = SasTokenFactory{value.password, value.host + "/devices/" + value.user};
}

void AzureHttp::close()
{
  sender = nullptr;
  receiver = nullptr;
}

void AzureHttp::setMessageCallback(Session::Callback function)
{
  listener = function;
}

