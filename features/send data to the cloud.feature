# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

Feature: Send data to the cloud
  As a city
  I want to know the light situation on the streets
  In order to selectively turn street lamps on or off

Scenario Outline: Forward the sensor data to the cloud
  Given I have a DBus streetlight
  And the brightness is <brightness>
  And the moisture is <moisture>
  And the proximity sensor returns <displacement>
  And I connect to the local mqtt broker
  And I start streetlightd

  When I tell streetlightd to update

  Then I expect one mqtt message with the content:
    """
    brightness <brightness>
    moisture <moisture>
    proximity <displacement>

    """

  Examples:
    | brightness | moisture | displacement |
    | 0          | 0.3      |  0.4         |
    | 0.42       | 0        | -0.5         |
    | 0.57       | 0.9      |  0.9         |
    | 1          | 0.14     | -0.3         |

