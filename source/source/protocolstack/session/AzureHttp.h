/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef AZUREHTTP_H
#define AZUREHTTP_H

#include "Session.h"
#include "http/Transfer.h"
#include "http/Session.h"
#include <infrastructure/SasToken.h>
#include <infrastructure/concurrency/Timer.h>

#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/URI.h>

/**
 * Azure connection via HTTP/1.1 through Poco.
 */
class AzureHttp :
    public Session
{
public:
  AzureHttp();

  void send(const presentation::Message &message) override;

  void setConfiguration(const session::Configuration &value) override;
  void connect() override;
  void close() override;

  void setMessageCallback(Callback function) override;

private:
  Callback listener{};
  std::string uriGet{};
  std::string uriPost{};
  SasTokenFactory tokenFactory{"", ""};

  std::unique_ptr<http::Session> sender{};
  std::unique_ptr<concurrency::Timer> receiver{};

};

#endif
