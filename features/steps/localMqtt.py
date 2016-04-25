# -*- coding: utf-8 -*-

# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

import paho.mqtt.client as mqtt

class LocalMqtt:
	def __init__(self):
		self.messages = []
		self.subscribed = False

		self.client = mqtt.Client()
		self.client.on_connect = self.on_connect
		self.client.on_subscribe = self.on_subscribe
		self.client.on_message = self.on_message
		self.client.on_publish = self.on_publish
		self.client.connect("localhost", 1883, 60)

		while not self.subscribed:
			self.client.loop(1)

	def cleanup(self):
		self.publish(None)


	def waitForMessage(self):
		while not self.messages:
			self.client.loop(1)


	def publish(self, message):
		self.published = False
		self.client.publish("streetlight/lamp1/actor", payload=message, qos=2, retain=True)
		while not self.published:
			self.client.loop(1)

	def on_connect(self, client, userdata, flags, rc):
		if rc <> 0:
			raise NotImplementedError('could not connect: ' + str(rc))

		self.client.subscribe("streetlight/lamp1/sensor")
		self.connected = True

	def on_subscribe(self, client, userdata, mid, granted_qos):
		self.subscribed = True

	def on_message(self, client, userdata, msg):
		self.messages.append(msg)

	def on_publish(self, mosq, obj, mid):
		self.published = True


