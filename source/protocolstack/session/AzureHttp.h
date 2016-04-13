/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef AZUREHTTP_H
#define AZUREHTTP_H

#include "Session.h"
#include "HttpTransfer.h"

#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/URI.h>
#include <memory>

class AzureHttp :
    public Session
{
public:
  AzureHttp();

  void send(const std::string &message) override;

  void setConfiguration(const SessionConfiguration &value) override;
  void setUp() override;
  void connect() override;
  void close() override;

  void setMessageCallback(Callback function) override;

private:
  Callback listener{};

  SessionConfiguration configuration{};
  Poco::URI uri{};
  std::unique_ptr<Poco::Net::HTTPSClientSession> session{};

  void handleResponseCode(const HttpTransfer &transfer) const;

};

#endif
