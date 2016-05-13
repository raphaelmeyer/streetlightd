# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

import subprocess
import dbus
import time

def startStreetlightd(context, layers):
	context.application = subprocess.Popen(['streetlightd', '--host=localhost', '--user=lamp1', '--external-timer'] + layers)

	bus = dbus.SessionBus()
	while not (dbus.UTF8String('ch.bbv.streetlightd') in bus.list_names()):
		time.sleep(0.01)

@given(u'I start streetlightd')
def step_impl(context):
	startStreetlightd(context, ['--application=forwarder', '--presentation=key-value', '--session=simple-mqtt'])

@given(u'I start streetlightd with the binary encoding')
def step_impl(context):
	startStreetlightd(context, ['--application=forwarder', '--presentation=binary', '--session=simple-mqtt'])

@given(u'I start streetlightd in the offline mode')
def step_impl(context):
	startStreetlightd(context, ['--application=offline', '--presentation=none', '--session=none'])

@when(u'I start session-test with the arguments "simple-mqtt" "hello world"')
def step_impl(context):
	context.application = subprocess.Popen(['session-test', 'simple-mqtt', 'localhost', 'lamp1', '', 'hello world'])

@when(u'I run {application} with no arguments')
def step_impl(context, application):
	context.app = subprocess.Popen([application], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	context.app.wait()

@when(u'I run azure-sas-token arguments {key} {scope} {expiration} {absolute}')
def step_impl(context, key, scope, absolute, expiration):
	context.app = subprocess.Popen(['azure-sas-token', key, scope, expiration, absolute], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	context.app.wait()

@then(u'I expect the following output of stdout')
def step_impl(context):
	expected = context.text
	output = context.app.stdout.read()
	assert output == expected, 'expected to see:\n' + expected + '\ngot:\n' + output + '\n'

