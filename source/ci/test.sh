#!/bin/bash

set -e

# start DBus
if test -z "$DBUS_SESSION_BUS_ADDRESS" ; then
	eval `dbus-launch --sh-syntax`
fi

# start MQTT server
service mosquitto start

# set paths
export PATH=`pwd`:${PATH}
cd features

# test
./unit-test
behave

