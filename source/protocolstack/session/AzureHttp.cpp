/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "AzureHttp.h"

#include "HttpTransfer.h"

#include <Poco/Exception.h>
#include <Poco/Net/Context.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Path.h>
#include <Poco/URI.h>

#include <iostream>

//TODO poll server

AzureHttp::AzureHttp()
{
}

void AzureHttp::connect()
{
  const auto ptrContext = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "", "", "", Poco::Net::Context::VERIFY_STRICT, 9, true, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
  const auto sp = new Poco::Net::HTTPSClientSession(uri.getHost(), uri.getPort(), ptrContext);
  session = std::unique_ptr<Poco::Net::HTTPSClientSession>{sp};
  session->setKeepAlive(true);
}

void AzureHttp::send(const std::string &message)
{
  HttpTransfer transfer{*session};

  transfer.setUri(uri.getPathAndQuery());
  transfer.setCredentials(configuration.credential);
  transfer.setRequest(message);

  transfer.execute();

  handleResponseCode(transfer);
}

void AzureHttp::setConfiguration(const SessionConfiguration &value)
{
  configuration = value;
  uri = configuration.address;
}

void AzureHttp::handleResponseCode(const HttpTransfer &transfer) const
{
  switch (transfer.getStatus()) {
  case Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK:
  {
    listener(transfer.getResponse());
    break;
  }
  case Poco::Net::HTTPResponse::HTTPStatus::HTTP_NO_CONTENT:
  {
    break;
  }
  default:
  {
    std::cout << "unhandled response: " << transfer.getStatus() << " " << transfer.getReason() << std::endl;
    break;
  }
  }
}

void AzureHttp::close()
{
  session.release();
}

void AzureHttp::setMessageCallback(Session::Callback function)
{
  listener = function;
}
