/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef PRESENTATIONLISTENER_H
#define PRESENTATIONLISTENER_H

class PresentationListener
{
public:
  virtual ~PresentationListener() = default;

  virtual void luminosity(double) = 0;

};

#endif
