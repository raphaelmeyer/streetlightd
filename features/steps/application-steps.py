# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

import subprocess

@given(u'I start streetlightd')
def step_impl(context):
	#TODO replace with actual application
	context.proc = subprocess.Popen(['mosquitto_pub', '-h', 'localhost', '-t', 'devices/Device1/messages/devicebound/test', '-m', 'brightness 0.34\n'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	#TODO do not wait (but kill app when finished?)
	context.proc.wait()

