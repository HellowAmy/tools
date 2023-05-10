TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ../../../test/hook/hook.c \
        main.c

HEADERS += \
    Tlist_c.h \
    htools.h \
    str_sc.h
