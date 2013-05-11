TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    matchstate.cpp \
    statemanager.cpp \
    game.cpp \
    gamestate.cpp \
    menustate.cpp

HEADERS += \
    gamestate.h \
    matchstate.h \
    statemanager.h \
    game.h \
    statechangetype.h \
    colorcodes.h \
    debugoutput.h \
    menustate.h \
    stateevent.h

QMAKE_CXXFLAGS += -std=c++0x

OTHER_FILES += \
    SourceSansPro-Light.ttf \
    todo.txt \
    Farbcodes.txt

unix:!macx:!symbian: LIBS += -L$$PWD/../sfml-build/lib/ -lsfml-system
unix:!macx:!symbian: LIBS += -L$$PWD/../sfml-build/lib/ -lsfml-window
unix:!macx:!symbian: LIBS += -L$$PWD/../sfml-build/lib/ -lsfml-graphics

INCLUDEPATH += $$PWD/sfml/include
DEPENDPATH += $$PWD/sfml/include
