#!/usr/bin/python

import dbus
 
bus = dbus.SessionBus()
streetlightd = bus.get_object('ch.bbv.streetlightd', '/ch/bbv/streetlightd')
streetlightd.timeout(dbus_interface='ch.bbv.timer')

