/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Null.h"

namespace presentation
{

namespace null
{

void Parser::reset(const Message &)
{
}

message::Property Parser::parseProperty()
{
  throw std::invalid_argument("no more data");
}

bool Parser::hasMore() const
{
  return false;
}

void Parser::parse(double &)
{
  throw std::invalid_argument("no more data");
}

void Parser::parse(std::string &)
{
  throw std::invalid_argument("no more data");
}

void PrintFormat::incomingHeader()
{
}

void PrintFormat::outgoingHeader()
{
}

void PrintFormat::footer()
{
}

void PrintFormat::value(bool, message::Property, double)
{
}

void PrintFormat::value(bool, message::Property, const std::__cxx11::string &)
{
}

Message PrintFormat::message() const
{
  return {};
}

}

}
