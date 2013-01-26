TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    gameengine.cpp \
    introstate.cpp

HEADERS += \
    gameengine.h \
    gamestate.h \
    introstate.h


LIBS += -lsfml-system -lsfml-window -lsfml-graphics

QMAKE_CXXFLAGS += -std=c++0x

OTHER_FILES += \
    intro.svg \
    intro.png
