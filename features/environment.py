# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

def after_scenario(context, scenario):
	context.dbus.remove_from_connection()

