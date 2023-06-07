TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpthread

SOURCES += \
        main.cpp \
        scan_op.cpp

HEADERS += \
    scan_op.h
