TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    gameengine.cpp

HEADERS += \
    gameengine.h \
    gamestate.h


LIBS += -lsfml-system -lsfml-window
