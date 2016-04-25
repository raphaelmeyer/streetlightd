# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

import dbus
import time
import subprocess


@given(u'I have a DBus streetlight')
def step_impl(context):
	#TODO make it independent of working directory
	context.dbus = subprocess.Popen(['python', 'steps/streetlight.py'])
	bus = dbus.SessionBus()
	while not (dbus.UTF8String('ch.bbv.streetlight') in bus.list_names()):
		time.sleep(0.01)

@given(u'the brightness is {value:g}')
def step_impl(context, value):
	bus = dbus.SessionBus()
	streetlightd = bus.get_object('ch.bbv.streetlight', '/ch/bbv/streetlight')
	streetlightd.Set('ch.bbv.brightness', 'scaled', dbus.Double(value), dbus_interface=dbus.PROPERTIES_IFACE)

@given(u'the moisture is {value:g}')
def step_impl(context, value):
	bus = dbus.SessionBus()
	streetlightd = bus.get_object('ch.bbv.streetlight', '/ch/bbv/streetlight')
	streetlightd.Set('ch.bbv.moisture', 'scaled', dbus.Double(value), dbus_interface=dbus.PROPERTIES_IFACE)

@given(u'the proximity sensor returns {value:g}')
def step_impl(context, value):
	bus = dbus.SessionBus()
	streetlightd = bus.get_object('ch.bbv.streetlight', '/ch/bbv/streetlight')
	streetlightd.Set('ch.bbv.proximity', 'scaled', dbus.Double(value), dbus_interface=dbus.PROPERTIES_IFACE)

@when(u'I tell streetlightd to update')
def step_impl(context):
	bus = dbus.SessionBus()
	streetlightd = bus.get_object('ch.bbv.streetlightd', '/ch/bbv/streetlightd')
	streetlightd.timeout(dbus_interface='ch.bbv.timer')

@then(u'I expect the lamp to have the luminosity {value:g}')
def step_impl(context, value):
	time.sleep(0.1)		#TODO is there a better way than sleep?
	bus = dbus.SessionBus()
	streetlightd = bus.get_object('ch.bbv.streetlight', '/ch/bbv/streetlight')
	luminosity = streetlightd.Get('ch.bbv.luminosity', 'scaled', dbus_interface=dbus.PROPERTIES_IFACE)
	assert value == luminosity, 'expected luminosity: ' + str(value) + ', got: ' + str(luminosity)

@then(u'I expect the lamp to show the warning \"{value}\"')
def expect_warning(context, value):
	time.sleep(0.1)		#TODO is there a better way than sleep?
	bus = dbus.SessionBus()
	streetlightd = bus.get_object('ch.bbv.streetlight', '/ch/bbv/streetlight')
	luminosity = streetlightd.Get('ch.bbv.warning', 'phrase', dbus_interface=dbus.PROPERTIES_IFACE)
	assert value == luminosity, 'expected warning: ' + str(value) + ', got: ' + str(luminosity)

@then(u'I expect the lamp to show the warning ""')	# workaround for empty string
def step_impl(context):
	expect_warning(context, "")

