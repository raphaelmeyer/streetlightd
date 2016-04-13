# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

import subprocess
import dbus
import time

@given(u'I start streetlightd')
def step_impl(context):
	context.application = subprocess.Popen(['streetlightd', '--application=forwarder', '--presentation=key-value', '--session=mqtt-local', '--external-timer'])

	bus = dbus.SessionBus()
	while not (dbus.UTF8String('ch.bbv.streetlightd') in bus.list_names()):
		time.sleep(0.01)

