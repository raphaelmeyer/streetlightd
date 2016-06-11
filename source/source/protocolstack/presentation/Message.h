/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef PRESENTATION_MESSAGE_H
#define PRESENTATION_MESSAGE_H

#include <string>
#include <vector>

namespace presentation
{

class Message final
{
public:
  Message();
  Message(const char *content);
  Message(const std::string &content);
  Message(const void *content, size_t length);
  Message(const std::vector<std::uint8_t> &content);

  std::string asString() const;
  std::vector<std::uint8_t> asBinary() const;

private:
  std::vector<std::uint8_t> content;

};

}

#endif
