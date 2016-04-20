/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Transfer.h"

namespace http
{

Transfer::Transfer(Poco::Net::HTTPClientSession &_session) :
  session{_session}
{
  request.setMethod(Poco::Net::HTTPRequest::HTTP_POST);
  request.setVersion(Poco::Net::HTTPMessage::HTTP_1_1);
}

void Transfer::setUri(const std::string &value)
{
  request.setURI(value);
}

void Transfer::setCredentials(const std::string &value)
{
  request.add("Authorization", value);
}

void Transfer::setRequest(const std::string &value)
{
  requestData = value;

  request.setContentType("application/octet-stream");   //TODO use correct type
  request.setContentLength(requestData.length());
}

void Transfer::execute()
{
  sendRequest();
  receiveResponse();
}

Poco::Net::HTTPResponse::HTTPStatus Transfer::getStatus() const
{
  return response.getStatus();
}

const std::string &Transfer::getReason() const
{
  return response.getReason();
}

const std::string &Transfer::getResponse() const
{
  return responseData;
}

void Transfer::sendRequest()
{
  auto &stream = session.sendRequest(request);
  stream << requestData;
}

void Transfer::receiveResponse()
{
  std::istream &stream = session.receiveResponse(response);
  stream >> responseData;
}

}
