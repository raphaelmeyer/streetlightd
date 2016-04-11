/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef KEYVALUEDECODER_H
#define KEYVALUEDECODER_H

#include "SessionListener.h"

#include <functional>
#include <string>

class KeyValueDecoder :
    public SessionListener
{
public:
  typedef std::function<void(double luminosity)> Listener;

  void setListener(Listener value);

  void decode(const std::string &message) override;

private:
  Listener listener{};

};

#endif
