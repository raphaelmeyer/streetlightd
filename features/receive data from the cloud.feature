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

Scenario Outline: Receive a warning and show it on the scoreboard
  Given I have a DBus streetlight
  And I connect to the local mqtt broker
  And I start streetlightd

  When I send a mqtt message with the content:
    """
    warning <value>

    """

  Then I expect the lamp to show the warning "<value>"

  Examples:
    | value                                   |
    |                                         |
    | hello                                   |
    | hello world                             |
    | I can write very long text to the board |

@wip
Scenario: Receive binary data from the cloud
  Given I have a DBus streetlight
  And I connect to the local mqtt broker
  And I start streetlightd with the binary encoding

  When I send a mqtt message with the binary content "03 05 68 65 6c 6c 6f 02 2a"

  Then I expect the lamp to show the warning "hello"
  And I expect the lamp to have the luminosity 0.42

