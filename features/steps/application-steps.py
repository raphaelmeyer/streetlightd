# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

import subprocess
import dbus
import time

def start(context, layers):
	context.application = subprocess.Popen(['streetlightd', '--host=localhost', '--user=lamp1', '--external-timer'] + layers)

	bus = dbus.SessionBus()
	while not (dbus.UTF8String('ch.bbv.streetlightd') in bus.list_names()):
		time.sleep(0.01)

@given(u'I start streetlightd')
def step_impl(context):
	start(context, ['--application=forwarder', '--presentation=key-value', '--session=simple-mqtt'])

@given(u'I start streetlightd with the binary encoding')
def step_impl(context):
	start(context, ['--application=forwarder', '--presentation=binary', '--session=simple-mqtt'])

@given(u'I start streetlightd in the offline mode')
def step_impl(context):
	start(context, ['--application=offline', '--presentation=none', '--session=none'])

