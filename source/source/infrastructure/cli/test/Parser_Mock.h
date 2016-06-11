/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef CLI_PARSER_MOCK_H
#define CLI_PARSER_MOCK_H

#include "../Parser.h"

#include <gmock/gmock.h>

namespace cli
{

class ParserMock :
    public Parser
{
public:
  MOCK_METHOD2(parse, void(const std::vector<std::string> &, const Poco::Util::OptionSet &));
  MOCK_CONST_METHOD0(printHelp, void());
  MOCK_CONST_METHOD0(isValid, bool());
  MOCK_CONST_METHOD1(value, std::string(const std::string &));
  MOCK_CONST_METHOD2(value, std::string(const std::string &, const std::string &));
  MOCK_CONST_METHOD1(contains, bool(const std::string &));

};

}

#endif
