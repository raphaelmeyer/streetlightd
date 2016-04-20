/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Message.h"

#include <cstring>
#include <algorithm>

namespace presentation
{

Message::Message() :
  content{}
{
}

Message::Message(const char *_content) :
  content{_content, _content + strlen(_content)}
{
}

Message::Message(const std::string &_content) :
  content{_content.c_str(), _content.c_str() + _content.size()}
{
}

Message::Message(const void *content, size_t length) :
  content{(uint8_t*)content, ((uint8_t*)content)+length}
{
}

Message::Message(const std::vector<uint8_t> &_content) :
  content{_content}
{
}

std::string Message::asString() const
{
  std::string result{};
  result.resize(content.size());
  std::transform(content.begin(), content.end(), result.begin(), [](uint8_t sym){return sym;});
  return result;
}

std::vector<uint8_t> Message::asBinary() const
{
  return content;
}


}
