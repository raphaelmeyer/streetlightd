#!/usr/bin/python

import dbus
import dbus.service
import dbus.mainloop.glib
import gobject
import glib
 
class Streetlight(dbus.service.Object):
    def __init__(self):
        self.session_bus = dbus.SessionBus()
	self.brightness = -1;
        name = dbus.service.BusName("ch.bbv.StreetLight", bus=self.session_bus)
        dbus.service.Object.__init__(self, name, '/StreetLight')

    @dbus.service.method(dbus.PROPERTIES_IFACE, in_signature='ss', out_signature='v')
    def Get(self, interface_name, property_name):
        return dbus.Double(self.brightness)

    @dbus.service.method(dbus.PROPERTIES_IFACE, in_signature='ssv')
    def Set(self, interface_name, property_name, value):
        self.brightness = value

    @dbus.service.method(dbus.PROPERTIES_IFACE, in_signature='s', out_signature='a{sv}')
    def GetAll(self, interface_name):
	if interface_name == 'ch.bbv.StreetLight.Brightness':
	        return { 'brightness': dbus.Double(self.brightness) }
	elif interface_name == 'ch.bbv.StreetLight.Lamp':
		return {}
	else:
		raise dbus.exceptions.DBusException('Unknown interface: ' + interface_name)

    @dbus.service.method("ch.bbv.StreetLight.Lamp", in_signature='d')
    def set(self, value):
        pass

    @dbus.service.signal('ch.bbv.StreetLight.Brightness', signature='d')
    def update(self, value):
        pass


if __name__ == '__main__':
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
    loop = gobject.MainLoop()
    streetlight = Streetlight()
    loop.run()

