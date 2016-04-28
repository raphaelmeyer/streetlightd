# streetlightd

This is a program which connects the Microsoft Azure Cloud (C) with D-Bus.
It is the counter part to [street-light-simulator](https://github.com/bbvch/street-light-simulator).

# What

This will connect to a specified d-bus object (ch/bbv/streetlight) and read the values of two interfaces (ch.bbv.brightness and ch.bbv.luminosity).
On change it will propagate the value of brightness to the Azure Cloud via AMQP, MQTT or HTTP.
The program can also receive luminosity values via the Cloud and propagate this value to the d-bus object.

# Why

This program is used for a bbv internal workshop.
It might also be useful to show people how to connect to the Azure Cloud.

#Who

This program is authored by [bbv Software Services AG](https://www.bbv.ch).

#Prerequisites

Installed  at least version **1.4.8** of libmosquitto-dev, libmosquittopp0-dev, libmosquittopp0.
You will also need libdus-c++, build-essential, libgtest-dev, google-mock, libpoco-dev, libcrypto++-dev libjsoncpp-dev libssl-dev. On Ubuntu Xenial all these packages can be installed by the command

    sudo apt-get install libmosquittopp-dev libmosquittopp1 libmosquitto-dev libdbus-c++ build-essential libgtest-dev google-mock libpoco-dev libcrypto++-dev libjsoncpp-dev libssl-dev

**After installation you will have to build gtest and gmock like [this](http://askubuntu.com/questions/145887/why-no-library-files-installed-for-google-test)**

The azure sdk needs following packages installed

    sudo apt-get install libcurl4-openssl-dev uuid-dev

*There might be more prerequisites for the project at the moment, let us now if you find any which should be included here.*



#License

This program is licensed under the GNU V3 license.
