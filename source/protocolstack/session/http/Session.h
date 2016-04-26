/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef HTTP_SESSION_H
#define HTTP_SESSION_H

#include "../Session.h"
#include "Transfer.h"
#include <infrastructure/SasToken.h>

#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/URI.h>
#include <memory>

namespace http
{

class Session final
{
public:
  Session(const Poco::URI &uri, const SasTokenFactory &tokenFactory);
  ~Session();

  std::string get();
  void post(const std::string &content);

private:
  Poco::URI uri{};
  const SasTokenFactory &tokenFactory;

  std::unique_ptr<Poco::Net::HTTPSClientSession> handle{};

  std::string transfer(const std::string &method, const std::string &content);
  std::string handleResponseCode(const Transfer &transfer) const;
};

}

#endif
