/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef HTTPTRANSFER_H
#define HTTPTRANSFER_H

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>

namespace http
{

class Transfer
{
public:
  Transfer(Poco::Net::HTTPClientSession &session);

  void setMethod(const std::string &value);
  void setUri(const std::string &value);
  void setCredentials(const std::string &credentials);
  void setRequest(const std::string &value);

  void execute();

  Poco::Net::HTTPResponse::HTTPStatus getStatus() const;
  const std::string &getReason() const;
  const std::string &getResponse() const;

private:
  Poco::Net::HTTPClientSession &session;
  Poco::Net::HTTPRequest request;
  Poco::Net::HTTPResponse response;
  std::string requestData{};
  std::string responseData{};

  void sendRequest();
  void receiveResponse();
  void handleResponseCode(const Poco::Net::HTTPResponse &response, const std::string &message);

};

}

#endif
