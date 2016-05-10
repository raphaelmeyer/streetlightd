# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

Feature: Test session with a simple application
  As a developer
  I want to test the session layer without the whole application
  In order to fastly detect and fix bugs

Scenario: Send a message to the local mqtt broker
  Given I connect to the local mqtt broker

  When I start session-test with the arguments "simple-mqtt" "hello world"

  Then I expect one mqtt message with the content:
    """
    hello world
    """

