/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "SasToken.h"

#include <crypto++/hmac.h>
#include <crypto++/sha.h>
#include <crypto++/base64.h>

#include <Poco/URI.h>

#include <sstream>

namespace sastoken
{

std::vector<uint8_t> hash(const std::vector<uint8_t> &key, const std::string &secret)
{
  CryptoPP::HMAC<CryptoPP::SHA256> engine(key.data(), key.size());

  std::vector<uint8_t> digest;
  digest.resize(engine.DigestSize());

  engine.Update((const byte*)secret.c_str(), secret.size());
  engine.Final(digest.data());

  return digest;
}

std::string encode(const std::vector<uint8_t> &data)
{
  std::string result;

  CryptoPP::Base64Encoder baseEncoder(new CryptoPP::StringSink(result), false);
  baseEncoder.Put(data.data(), data.size());
  baseEncoder.MessageEnd();

  return result;
}

std::vector<uint8_t> decode(const std::string &data)
{
  std::vector<uint8_t> result;

  CryptoPP::Base64Decoder baseDecoder{};
  baseDecoder.Put((const byte*)data.c_str(), data.size());
  baseDecoder.MessageEnd();

  result.resize(baseDecoder.MaxRetrievable());
  const auto read = baseDecoder.Get(result.data(), result.size());

  if (read != result.size()) {
    throw std::runtime_error("Could not retreive all data from CryptoPP::Base64Decoder");
  }

  return result;
}

std::string urlEncode(const std::string &data)
{
  std::string result;

  Poco::URI::encode(data, "+/=", result);

  return result;
}

std::string sharedAccessSignature(const std::string &scope, const std::string &signature, const std::string &expiration, const std::string &keyname)
{
  std::stringstream result;

  result << "SharedAccessSignature" << " ";
  result << "sr="  << scope << "&";
  result << "sig=" << signature << "&";
  result << "se="  << expiration << "&";
  result << "skn=" << keyname;

  return result.str();
}

std::string secret(const std::string &scope, const std::string &expiration)
{
  return scope + "\n" + expiration;
}

}

SasTokenFactory::GetTime SasTokenFactory::currentTimeReader()
{
  return []{
    return std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
  };
}

SasTokenFactory::SasTokenFactory(const std::string &encodedKey, const std::string &scope) :
  SasTokenFactory(encodedKey, scope, currentTimeReader())
{
}

SasTokenFactory::SasTokenFactory(const std::string &_encodedKey, const std::string &_scope, GetTime _getTime) :
  key{sastoken::decode(_encodedKey)},
  scope{_scope},
  getTime{_getTime}
{
}

SasTokenFactory::SasTokenFactory(const std::string &_encodedKey, const std::string &_scope, long long _seconds):
    key{sastoken::decode(_encodedKey)},
    scope{_scope},
    getTime{currentTimeReader()},
    validityDuration{std::chrono::seconds(_seconds)}
{
}

std::string SasTokenFactory::produce() const
{
  const auto expiration = calcExpirationString();
  const auto secret = sastoken::secret(scope, expiration);
  const auto signature = sastoken::hash(key, secret);
  const auto encodedSignature = sastoken::urlEncode(sastoken::encode(signature));

  return sastoken::sharedAccessSignature(scope, encodedSignature, expiration, "");
}

std::chrono::seconds SasTokenFactory::getValidityDuration() const
{
  return validityDuration;
}

void SasTokenFactory::setValidityDuration(std::chrono::seconds value)
{
  validityDuration = value;
}

std::string SasTokenFactory::calcExpirationString() const
{
  const auto secondsSince1970 = getTime() - Time{std::chrono::seconds{0}};
  const auto expiration = secondsSince1970 + validityDuration;
  return std::to_string(expiration.count());
}

