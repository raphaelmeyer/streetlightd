# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

Feature: Receive data from the cloud
  As a city
  I want to control the the street light
  In order to increase security and minimize energy consumption


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

Scenario: Receive binary data from the cloud
  Given I have a DBus streetlight
  And I connect to the local mqtt broker
  And I start streetlightd with the binary encoding

  When I send a mqtt message with the binary content "02 2a"

  Then I expect the lamp to have the luminosity 0.42

