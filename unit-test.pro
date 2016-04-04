# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lgmock_main -lgmock -lpthread

INCLUDEPATH += source/

SOURCES += \
    source/application/Application.cpp \
    source/application/test/Application_Test.cpp \
    source/presentation/KeyValueEncoder.cpp \
    source/presentation/test/KeyValueEncoder_Test.cpp \
    source/presentation/test/KeyValueDecoder_Test.cpp \
    source/presentation/KeyValueDecoder.cpp

HEADERS += \
    source/application/Application.h \
    source/application/Presentation.h \
    source/application/test/Presentation_Mock.h \
    source/presentation/KeyValueEncoder.h \
    source/presentation/Session.h \
    source/presentation/test/Session_Mock.h \
    source/application/Actor.h \
    source/application/test/Actor_Mock.h \
    source/application/Sensor.h \
    source/application/test/Sensor_Mock.h \
    source/application/PresentationListener.h \
    source/presentation/KeyValueDecoder.h \
    source/application/test/PresentationListener_Mock.h \
    source/presentation/SessionListener.h
