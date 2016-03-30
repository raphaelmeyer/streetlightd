# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

import paho.mqtt.client as mqtt

class AzureMqtt:
	def __init__(self):
		self.messages = []
		self.subscribed = False

		self.client = mqtt.Client()
		self.client.on_connect = self.on_connect
		self.client.on_subscribe = self.on_subscribe
		self.client.on_message = self.on_message
		self.client.connect("localhost", 1883, 60)

		while not self.subscribed:
			self.client.loop(1)

	def waitForMessage(self):
		while not self.messages:
			self.client.loop(1)

	def on_connect(self, client, userdata, flags, rc):
		if rc <> 0:
			raise NotImplementedError('could not connect: ' + str(rc))

		self.client.subscribe("devices/Device1/messages/devicebound/#")
		self.connected = True

	def on_subscribe(self, client, userdata, mid, granted_qos):
		self.subscribed = True

	def on_message(self, client, userdata, msg):
		self.messages.append(msg)


@given(u'I subscribe to the azure receive topic on the local mqtt broker')
def step_impl(context):
	context.mqtt = AzureMqtt();

@then(u'I expect one mqtt message with the content')
def step_impl(context):
	context.mqtt.waitForMessage()

	numberOfMessages = len(context.mqtt.messages)
	assert numberOfMessages == 1, 'expected 1 message, got ' + str(numberOfMessages)\

	message = context.mqtt.messages[0]
	assert str(message.payload) == context.text, 'expected message:\n' + context.text + '\ngot:\n' + str(message.payload) + '\n----'

