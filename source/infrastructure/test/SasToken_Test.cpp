/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "../SasToken.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <chrono>

TEST(SasToken_Test, generate_empty_hash)
{
  const std::vector<uint8_t> key = {};
  const std::string secret = "";
  const std::vector<uint8_t> expectedHash = {0xb6, 0x13, 0x67, 0x9a, 0x08, 0x14, 0xd9, 0xec, 0x77, 0x2f, 0x95, 0xd7, 0x78, 0xc3, 0x5f, 0xc5, 0xff, 0x16, 0x97, 0xc4, 0x93, 0x71, 0x56, 0x53, 0xc6, 0xc7, 0x12, 0x14, 0x42, 0x92, 0xc5, 0xad};

  const std::vector<uint8_t> hash = sastoken::hash(key, secret);

  ASSERT_EQ(expectedHash, hash);
}

TEST(SasToken_Test, generate_non_empty_hash)
{
  const std::vector<uint8_t> key = {'k', 'e', 'y'};
  const std::string secret = "The quick brown fox jumps over the lazy dog";
  const std::vector<uint8_t> expectedHash = {0xf7, 0xbc, 0x83, 0xf4, 0x30, 0x53, 0x84, 0x24, 0xb1, 0x32, 0x98, 0xe6, 0xaa, 0x6f, 0xb1, 0x43, 0xef, 0x4d, 0x59, 0xa1, 0x49, 0x46, 0x17, 0x59, 0x97, 0x47, 0x9d, 0xbc, 0x2d, 0x1a, 0x3c, 0xd8};

  const std::vector<uint8_t> hash = sastoken::hash(key, secret);

  ASSERT_EQ(expectedHash, hash);
}

TEST(SasToken_Test, encode_to_base64)
{
  const std::vector<uint8_t> data = {'s', 'u', 'r', 'e', '.'};
  const std::string expected = "c3VyZS4=";

  const std::string encoded = sastoken::encode(data);

  ASSERT_EQ(expected, encoded);
}

TEST(SasToken_Test, decode_from_base64)
{
  const std::string data = "c3VyZS4=";
  const std::vector<uint8_t> expected = {'s', 'u', 'r', 'e', '.'};

  const std::vector<uint8_t> encoded = sastoken::decode(data);

  ASSERT_EQ(expected, encoded);
}

TEST(SasToken_Test, url_encode_special_characters)
{
  ASSERT_EQ("%2B", sastoken::urlEncode("+"));
  ASSERT_EQ("%2F", sastoken::urlEncode("/"));
  ASSERT_EQ("%3D", sastoken::urlEncode("="));
}

TEST(SasToken_Test, url_encode_in_a_string)
{
  const std::string original = "test+for/special=";
  const std::string expected = "test%2Bfor%2Fspecial%3D";

  const std::string encoded = sastoken::urlEncode(original);

  ASSERT_EQ(expected, encoded);
}

TEST(SasToken_Test, create_secret)
{
  const std::string expected = "SCOPE\nEXPIRATION";

  const std::string secret = sastoken::secret("SCOPE", "EXPIRATION");

  ASSERT_EQ(expected, secret);
}

TEST(SasToken_Test, create_shared_access_signature)
{
  const std::string expected = "SharedAccessSignature sr=SCOPE&sig=SIGNATURE&se=EXPIRATION&skn=KEYNAME";

  const std::string signature = sastoken::sharedAccessSignature("SCOPE", "SIGNATURE", "EXPIRATION", "KEYNAME");

  ASSERT_EQ(expected, signature);
}

TEST(SasToken_Test, create_sas_token)
{
  const std::string expected = "SharedAccessSignature sr=scope&sig=Z11UkW5tzlhaXIdegd7u%2BgnnD%2F0vaWvK0s0Oo7cRFU0%3D&se=1003600&skn=";
  SasTokenFactory::GetTime getTime = []{return SasTokenFactory::Time{std::chrono::seconds(1'000'000)};};
  SasTokenFactory testee{"c3VyZS4=", "scope", getTime};

  const std::string token = testee.produce();

  ASSERT_EQ(expected, token);
}

TEST(SasToken_Test, default_expiration_time_is_one_hour)
{
  SasTokenFactory testee{"", ""};

  ASSERT_EQ(std::chrono::hours(1), testee.getValidityDuration());
}

TEST(SasToken_Test, changeing_validity_duration_produces_different_sas_tokens)
{
  const std::string expected = "SharedAccessSignature sr=scope&sig=rjy9dNcZbwnIntvffvMPaUauCcOFRvnKgklPOGdzFZQ%3D&se=1000042&skn=";
  SasTokenFactory::GetTime getTime = []{return SasTokenFactory::Time{std::chrono::seconds(1'000'000)};};
  SasTokenFactory testee{"c3VyZS4=", "scope", getTime};

  testee.setValidityDuration(std::chrono::seconds(42));

  ASSERT_EQ(expected, testee.produce());
}
