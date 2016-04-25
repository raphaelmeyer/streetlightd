# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

from localMqtt import *

@given(u'I connect to the local mqtt broker')
def step_impl(context):
	context.mqtt = LocalMqtt();

@when(u'I send a mqtt message with the content')
def step_impl(context):
	context.mqtt.publish(context.text)

@then(u'I expect one mqtt message with the content')
def step_impl(context):
	context.mqtt.waitForMessage()

	numberOfMessages = len(context.mqtt.messages)
	assert numberOfMessages == 1, 'expected 1 message, got ' + str(numberOfMessages)\

	message = context.mqtt.messages[0]
	assert str(message.payload) == context.text, 'expected message:\n' + context.text + '\ngot:\n' + str(message.payload) + '\n----'

