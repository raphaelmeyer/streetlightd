# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

Feature: Generate an Azure SAS token
  As a developer
  I want to generate an SAS token for Azure
  In order to test the conenction with an off the shelf application like curl or mosquitto_pub


Scenario Outline: generate a SAS token that is valid until a specific point in time
  When I run azure-sas-token arguments --key=<encoded key> --scope=<scope> --expiration=<valid until> --absolute

  Then I expect the following output of stdout:
    """
    <token>

    """

  Examples:
    | encoded key | scope                 | valid until | token                                                                                                        |
    | c3VyZS4=    | hal.azure-devices.net |          42 | SharedAccessSignature sr=hal.azure-devices.net&sig=lyVhVg8lF9gJPRYEf4BTgBBpidomOwnBPMRkl8vXweo%3D&se=42&skn= |
    | c3VyZS4=    | scope                 |     1003600 | SharedAccessSignature sr=scope&sig=Z11UkW5tzlhaXIdegd7u%2BgnnD%2F0vaWvK0s0Oo7cRFU0%3D&se=1003600&skn=        |


Scenario: The user gets a friendly usage message when she calls the application with wrong arguments
  When I run azure-sas-token with no arguments

  Then I expect the following output of stdout:
    """
    usage:  azure-sas-token --key=<> --scope=<> --expiration=<> [--absolute]
    --key=<key>                base64 encoded password
    --scope=<scope>            url
    --expiration=<expiration>  expiration time in seconds from now
    --absolute                 if given, expiration time not from now but from 1.1.1970

    """

