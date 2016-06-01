# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

Feature: Control multiple lamps from one device
  As a city
  I want to reduce the number of devices
  In order to save money

Scenario: connect streetlightd to a service with a different name
  Given I have a DBus streetlight with the name ch.bbv.streetlight42

  When I start streetlightd in the offline mode with the argument "--service=ch.bbv.streetlight42"

  Then I expect no error

