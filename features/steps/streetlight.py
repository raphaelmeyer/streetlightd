#!/usr/bin/python

# (C) Copyright 2016
# Urs Fassler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

import dbus
import dbus.service
import dbus.mainloop.glib
import gobject
import glib

class Streetlight(dbus.service.Object):
    def __init__(self):
        self.session_bus = dbus.SessionBus()
	self.brightness = -1
	self.luminosity = -1
        name = dbus.service.BusName("ch.bbv.StreetLight", bus=self.session_bus)
        dbus.service.Object.__init__(self, name, '/StreetLight')

    @dbus.service.method(dbus.PROPERTIES_IFACE, in_signature='ss', out_signature='v')
    def Get(self, interface_name, property_name):
        return self.GetAll(interface_name)[property_name]

    @dbus.service.method(dbus.PROPERTIES_IFACE, in_signature='ssv')
    def Set(self, interface_name, property_name, value):
        if interface_name == 'ch.bbv.StreetLight.Brightness':
            if property_name == 'value':
                self.brightness = value
        if interface_name == 'ch.bbv.luminosity':
            if property_name == 'scaled':
                self.luminosity = value


    @dbus.service.method(dbus.PROPERTIES_IFACE, in_signature='s', out_signature='a{sv}')
    def GetAll(self, interface_name):
	if interface_name == 'ch.bbv.StreetLight.Brightness':
	        return { 'value': dbus.Double(self.brightness) }
	elif interface_name == 'ch.bbv.luminosity':
	        return { 'scaled': dbus.Double(self.luminosity) }
	else:
		raise dbus.exceptions.DBusException('Unknown interface: ' + interface_name)


if __name__ == '__main__':
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
    loop = gobject.MainLoop()
    streetlight = Streetlight()
    loop.run()

