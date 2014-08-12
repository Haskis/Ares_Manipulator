#-------------------------------------------------
#
# Project created by QtCreator 2014-08-12T15:50:18
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = Ares_Manipulator
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(qextserialport/src/qextserialport.pri)

SOURCES += main.cpp \
    modbusserver.cpp \
    motordriver.cpp \
    manipulator.cpp

HEADERS += \
    modbus.h \
    modbusserver.h \
    motordriver.h \
    manipulator.h
