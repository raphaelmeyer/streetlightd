# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

LIBS += -lmosquittopp
LIBS += -ldbus-c++-1
LIBS += -pthread

SOURCES += \
    source/main.cpp \
    source/Mqtt.cpp

HEADERS += \
    source/Mqtt.h \
    source/StreetlightProxy.h

DISTFILES += \
    streetlight.dbus.xml

