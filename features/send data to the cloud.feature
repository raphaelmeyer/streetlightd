# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

Feature: Send data to the cloud
  As a city
  I want to know the light situation on the streets
  In order to selectively turn street lamps on or off


Scenario Outline: Receive a brightness value
  Given I have a DBus brightness sensor
  And the brightness is <value>
  And I subscribe to the azure receive topic on the local mqtt broker
  And I start streetlightd

  When I tell streetlightd to update

  Then I expect one mqtt message with the content:
    """
    brightness <value>

    """

  Examples:
    | value |
    | 0     |
    | 0.42  |
    | 0.57  |
    | 1     |

