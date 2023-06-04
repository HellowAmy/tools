TEMPLATE = app
#CONFIG += console c++11
CONFIG += c++11 console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        a.cpp \
        b.cpp \
        main.cpp \
        vts/vts.cpp

HEADERS += \
    Tvlog.h \
    a.h \
    b.h \
    vts/vts.h
