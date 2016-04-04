/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef KEYVALUEDECODER_H
#define KEYVALUEDECODER_H

#include "SessionListener.h"

#include <application/PresentationListener.h>

#include <string>

class KeyValueDecoder :
    public SessionListener
{
public:
  KeyValueDecoder(PresentationListener &listener);

  void decode(const std::string &message) override;

private:
  PresentationListener &listener;
};

#endif
