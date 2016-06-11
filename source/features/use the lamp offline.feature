# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

Feature: Use the streetlight without a cloud connection
  As a city
  I want to use the streetlight without a cloud connection
  In order to be independent of the conenctivity and/or the cloud provider

Scenario Outline: Turn the lamp on/off depending on the brightness
  Given I have a DBus streetlight
  And the brightness is <brightness>
  And I start streetlightd in the offline mode

  When I tell streetlightd to update

  Then I expect the lamp to have the luminosity <luminosity>

  Examples:
    | brightness | luminosity |
    | 0.0        | 1.0        |
    | 0.1        | 1.0        |
    | 0.2        | 1.0        |
    | 0.3        | 0.0        |
    | 0.4        | 0.0        |
    | 0.5        | 0.0        |
    | 0.6        | 0.0        |
    | 0.7        | 0.0        |
    | 0.8        | 0.0        |
    | 0.9        | 0.0        |
    | 1.0        | 0.0        |

