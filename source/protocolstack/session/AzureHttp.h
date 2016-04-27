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

#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/URI.h>
#include <memory>
#include <thread>

class AzureHttp :
    public Session
{
public:
  AzureHttp();

  void send(const presentation::Message &message) override;

  void setConfiguration(const SessionConfiguration &value) override;
  void connect() override;
  void close() override;

  void setMessageCallback(Callback function) override;

private:
  Callback listener{};
  std::string uriGet{};
  std::string uriPost{};
  SasTokenFactory tokenFactory{"", ""};

  std::unique_ptr<http::Session> sender{};

  bool receiverRunning;
  std::thread reader;

};

#endif
