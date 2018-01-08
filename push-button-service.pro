TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    pushbuttonservice.cpp \
    button.cpp \
    eventtime.cpp

HEADERS += \
    pushbuttonservice.h \
    button.h \
    eventtime.h \
    raspi.h

