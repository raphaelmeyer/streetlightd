# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

import dbus
import dbus.service
import dbus.mainloop.glib
import time

class StreetLight(dbus.service.Object):
    def __init__(self):
        self.session_bus = dbus.SessionBus()
        name = dbus.service.BusName("ch.bbv.StreetLight", bus=self.session_bus)
        dbus.service.Object.__init__(self, name, '/StreetLight')

    @dbus.service.method("ch.bbv.StreetLight.Lamp", in_signature='d')
    def set(self, value):
        pass

    @dbus.service.signal('ch.bbv.StreetLight.Brightness', signature='d')
    def update(self, value):
        pass


@given(u'I have a DBus brightness sensor')
def step_impl(context):
	dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
	context.dbus = StreetLight()
	import gobject
	context.main = gobject.MainContext()
	loop = gobject.MainLoop(context.main)
#	context.main.iteration(False)
#	loop.run()

@when(u'I signal a new brightness value of {value:g}')
def step_impl(context, value):
	time.sleep(0.1)		#TODO is there a better way than sleep?
	context.dbus.update(value)

