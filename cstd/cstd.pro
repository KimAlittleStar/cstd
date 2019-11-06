TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ../cset.c \
        ../cstackqueue.c \
        ../cvector.c \
        main.c

HEADERS += \
    ../cset.h \
    ../cstackqueue.h \
    ../cvector.h
