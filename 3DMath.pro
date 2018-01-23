TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    vector3d.cpp \
    vector4d.cpp \
    matrix4d.cpp

HEADERS += \
    vector3d.h \
    vector4d.h \
    matrix4d.h
