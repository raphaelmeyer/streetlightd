# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

INCLUDEPATH += /usr/include/dbus-c++-1/

LIBS += -lmosquittopp
LIBS += -ldbus-c++-1
LIBS += -pthread

SOURCES += \
    source/main.cpp \
    source/Application.cpp \
    source/KeyValueEncoder.cpp \
    source/BrightnessSensor.cpp \
    source/MqttTest.cpp \
    source/Timer.cpp

HEADERS += \
    source/StreetlightProxy.h \
    source/Application.h \
    source/KeyValueEncoder.h \
    source/Presentation.h \
    source/Session.h \
    source/BrightnessSensor.h \
    source/MqttTest.h \
    source/TimerAdaptor.h \
    source/Timer.h \
    source/TimerListener.h

DISTFILES += \
    streetlight.dbus.xml

OTHER_FILES += \
    streetlightd.dbus.xml

