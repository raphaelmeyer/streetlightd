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
INCLUDEPATH += source/

LIBS += -lmosquittopp
LIBS += -ldbus-c++-1
LIBS += -pthread

SOURCES += \
    source/main.cpp \
    source/application/Application.cpp \
    source/dbus/BrightnessSensor.cpp \
    source/dbus/Timer.cpp \
    source/presentation/KeyValueEncoder.cpp \
    source/session/LocalMqtt.cpp

HEADERS += \
    source/application/Application.h \
    source/application/Brightness.h \
    source/application/Presentation.h \
    source/application/TimerListener.h \
    source/dbus/BrightnessSensor.h \
    source/dbus/StreetlightProxy.h \
    source/dbus/TimerAdaptor.h \
    source/dbus/Timer.h \
    source/presentation/KeyValueEncoder.h \
    source/presentation/Session.h \
    source/session/LocalMqtt.h

OTHER_FILES += \
    streetlight.dbus.xml \
    streetlightd.dbus.xml

