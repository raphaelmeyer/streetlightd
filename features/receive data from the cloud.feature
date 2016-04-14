# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

Feature: Receive data from the cloud
  As a city
  I want to turn the light on the street on or off
  In order to minimize energy consumption


Scenario Outline: Receive a brightness value and set the lamp
  Given I have a DBus streetlight
  And I connect to the local mqtt broker
  And I start streetlightd

  When I send a mqtt message with the content:
    """
    luminosity <value>

    """

  Then I expect the lamp to have the luminosity <value>

  Examples:
    | value |
    | 0     |
    | 0.42  |
    | 0.57  |
    | 1     |

