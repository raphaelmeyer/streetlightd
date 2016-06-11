# streetlightd [![Build Status](https://travis-ci.org/raphaelmeyer/streetlightd.svg?branch=master)](https://travis-ci.org/raphaelmeyer/streetlightd)

This is a program which connects the Microsoft Azure Cloud (C) with D-Bus.
It is the counter part to [street-light-simulator](https://github.com/raphaelmeyer/street-light-simulator).

# What

This will connect to a specified d-bus object (ch/bbv/streetlight) and read the values of two interfaces (ch.bbv.brightness and ch.bbv.luminosity).
On change it will propagate the value of brightness to the Azure Cloud via AMQP, MQTT or HTTP.
The program can also receive luminosity values via the Cloud and propagate this value to the d-bus object.

# Why

This program is used for a bbv internal workshop.
It might also be useful to show people how to connect to the Azure Cloud.

# Who

This program is authored by [bbv Software Services AG](https://www.bbv.ch).

# How

Clone this repopsitory:

    git clone https://github.com/raphaelmeyer/streetlightd.git
    cd streetlightd
    git submodule update --init --recursive

Check the [continuous integration](ci/) part for build and test instructions.

# License

This program is licensed under the GNU V3 license.
