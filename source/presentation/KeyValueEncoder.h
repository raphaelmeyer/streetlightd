/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef KEYVALUEENCODER_H
#define KEYVALUEENCODER_H

#include <application/Presentation.h>

#include <string>
#include <functional>

/**
 * Own representation of key-value pairs that never should be used.
 *
 * document := { entry }
 * entry := identifier value '\n'
 * value := identifier | number
 */
class KeyValueEncoder :
    public Presentation
{
public:
  typedef std::function<void(const std::string&)> Listener;

  void setListener(Listener value);

  void brightness(double value) override;

private:
  Listener message{};

};

#endif
