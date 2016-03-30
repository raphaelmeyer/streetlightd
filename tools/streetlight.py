#!/usr/bin/python

import dbus
import dbus.service
import dbus.mainloop.glib
import gobject
import glib
 
class Streetlight(dbus.service.Object):
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

def tick(streetlight):
    streetlight.update(0.5)
    return True

if __name__ == '__main__':
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
    loop = gobject.MainLoop()
    streetlight = Streetlight()
    glib.timeout_add_seconds(1, tick, streetlight)
    loop.run()

