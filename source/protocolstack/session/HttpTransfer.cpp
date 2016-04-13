/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "HttpTransfer.h"

HttpTransfer::HttpTransfer(Poco::Net::HTTPClientSession &_session) :
  session{_session}
{
  request.setMethod(Poco::Net::HTTPRequest::HTTP_POST);
  request.setVersion(Poco::Net::HTTPMessage::HTTP_1_1);
}

void HttpTransfer::setUri(const std::string &value)
{
  request.setURI(value);
}

void HttpTransfer::setCredentials(const std::string &value)
{
  request.add("Authorization", value);
}

void HttpTransfer::setRequest(const std::string &value)
{
  requestData = value;

  request.setContentType("application/octet-stream");   //TODO use correct type
  request.setContentLength(requestData.length());
}

void HttpTransfer::execute()
{
  sendRequest();
  receiveResponse();
}

Poco::Net::HTTPResponse::HTTPStatus HttpTransfer::getStatus() const
{
  return response.getStatus();
}

const std::string &HttpTransfer::getReason() const
{
  return response.getReason();
}

const std::string &HttpTransfer::getResponse() const
{
  return responseData;
}

void HttpTransfer::sendRequest()
{
  auto &stream = session.sendRequest(request);
  stream << requestData;
}

void HttpTransfer::receiveResponse()
{
  std::istream &stream = session.receiveResponse(response);
  stream >> responseData;
}
