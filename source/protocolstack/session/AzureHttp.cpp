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

static void receiverThread(bool *running, std::unique_ptr<http::Session> session)
{
  //TODO improve exit with condition variable or something else

  while (*running) {
    session->get();

    for (int i = 0; (i < 10) && *running; i++) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  }
}


AzureHttp::AzureHttp()
{
}

void AzureHttp::connect()
{
  sender = std::unique_ptr<http::Session>(new http::Session(Poco::URI{uriPost}, tokenFactory));
  std::unique_ptr<http::Session> receiver = std::unique_ptr<http::Session>(new http::Session(Poco::URI{uriGet}, tokenFactory, [this](const auto &value){
    listener(value);
  }));

  receiverRunning = true;
  reader = std::thread{receiverThread, &receiverRunning, std::move(receiver)};
}

void AzureHttp::send(const presentation::Message &message)
{
  sender->post(message.asString());
}

void AzureHttp::setConfiguration(const SessionConfiguration &value)
{
  uriPost = "https://" + value.host + "/devices/" + value.user + "/messages/events?api-version=2016-02-03";
  uriGet = "https://" + value.host + "/devices/" + value.user + "/messages/devicebound?api-version=2016-02-03";
  tokenFactory = SasTokenFactory{value.password, value.host + "/devices/" + value.user};
}

void AzureHttp::close()
{
  receiverRunning = false;
  reader.join();

  sender.release();
}

void AzureHttp::setMessageCallback(Session::Callback function)
{
  listener = function;
}

