# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

import dbus
import time
import subprocess


@given(u'I have a DBus brightness sensor')
def step_impl(context):
	#TODO make it independent of working directory
	context.dbus = subprocess.Popen(['python', 'steps/streetlight.py'])

@given(u'the brightness is {value:g}')
def step_impl(context, value):
	time.sleep(0.1)		#TODO is there a better way than sleep?
	bus = dbus.SessionBus()
	streetlightd = bus.get_object('ch.bbv.StreetLight', '/StreetLight')
	streetlightd.Set('ch.bbv.StreetLight.Brightness', 'brightness', dbus.Double(value), dbus_interface=dbus.PROPERTIES_IFACE)

@when(u'I tell streetlightd to update')
def step_impl(context):
	bus = dbus.SessionBus()
	time.sleep(0.1)		#TODO is there a better way than sleep?
	streetlightd = bus.get_object('ch.bbv.streetlightd', '/ch/bbv/streetlightd')
	streetlightd.timeout(dbus_interface='ch.bbv.timer')

