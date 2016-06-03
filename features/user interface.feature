# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

Feature: Provide a nice user interface
  As a developer
  I want to get information about the command line interface
  In order to see when I provided wrong arguments


Scenario: print the help
  When I run streetlightd with no arguments

  Then I expect the following output of stdout:
    """
    usage: 
    -h, --help                         print this help
    -a<value>, --application=<value>   <value> is one of:
                                       debug
                                       forwarder
                                       offline
    -p<value>, --presentation=<value>  <value> is one of:
                                       binary
                                       json
                                       key-value
                                       none
    -s<value>, --session=<value>       <value> is one of:
                                       azure-amqp
                                       azure-amqp-ws
                                       azure-http
                                       azure-mqtt
                                       none
                                       simple-mqtt
    --host=<host>                      host to connect to
                                       for azure-* sessions, this is <iot hub name>.azure-devices.net
    --user=<user>                      username for the session
                                       for azure-* sessions, this is the device name
    --password=<password>              password for the session
                                       for azure-* sessions, this is the key
    --service=<name>                   connect to the service <name> instead of ch.bbv.streetlight
    --external-timer                   trigger updates via DBus

    """

