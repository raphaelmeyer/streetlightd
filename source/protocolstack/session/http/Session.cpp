/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Session.h"

#include "Transfer.h"

#include <Poco/Exception.h>
#include <Poco/Net/Context.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Path.h>
#include <Poco/URI.h>

namespace http
{

Session::Session(const Poco::URI &_uri, const SasTokenFactory &_tokenFactory, Callback _receiver) :
  uri{_uri},
  receiver{_receiver},
  tokenFactory{_tokenFactory}
{
  const auto ptrContext = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "", "", "", Poco::Net::Context::VERIFY_STRICT, 9, true, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");

  const auto handlePointer = new Poco::Net::HTTPSClientSession(uri.getHost(), uri.getPort(), ptrContext);
  handle = std::unique_ptr<Poco::Net::HTTPSClientSession>{handlePointer};
  handle->setKeepAlive(true);
}

void Session::get()
{
  transfer(Poco::Net::HTTPRequest::HTTP_GET, "");
}

void Session::post(const std::string &content)
{
  transfer(Poco::Net::HTTPRequest::HTTP_POST, content);
}

void Session::transfer(const std::string &method, const std::string &content)
{
  Transfer transfer{*handle};

  transfer.setMethod(method);
  transfer.setUri(uri.getPathAndQuery());
  transfer.setCredentials(tokenFactory.produce());
  transfer.setRequest(content);

  transfer.execute();

  return handleResponseCode(transfer);
}

void Session::handleResponseCode(const Transfer &transfer) const
{
  switch (transfer.getStatus()) {
  case Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK:
  {
    receiver(transfer.getResponse());
    break;
  }
  case Poco::Net::HTTPResponse::HTTPStatus::HTTP_NO_CONTENT:
  {
    break;
  }
  default:
  {
    throw std::runtime_error("Unexpected return code: " + std::to_string(transfer.getStatus()) + " " + transfer.getReason());
  }
  }
}

}

