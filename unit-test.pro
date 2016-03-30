# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lgmock_main -lgmock -lpthread

SOURCES += \
    source/KeyValueEncoder_Test.cpp \
    source/KeyValueEncoder.cpp

HEADERS += \
    source/Session_Mock.h \
    source/Session.h \
    source/KeyValueEncoder.h

