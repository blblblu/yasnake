TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    matchstate.cpp \
    statemanager.cpp \
    game.cpp \
    gamestate.cpp \
    menustate.cpp \
    player.cpp

HEADERS += \
    colorcodes.hpp \
    debugoutput.hpp \
    game.hpp \
    gamestate.hpp \
    matchstate.hpp \
    menustate.hpp \
    player.hpp \
    statemanager.hpp \
    stateevent.hpp \
    direction.hpp

QMAKE_CXXFLAGS += -std=c++0x

OTHER_FILES += \
    SourceSansPro-Light.ttf \
    todo.txt \
    Farbcodes.txt

unix:!macx:!symbian: LIBS += -L$$PWD/sfml/lib/ -lsfml-system
unix:!macx:!symbian: LIBS += -L$$PWD/sfml/lib/ -lsfml-window
unix:!macx:!symbian: LIBS += -L$$PWD/sfml/lib/ -lsfml-graphics


INCLUDEPATH += $$PWD/sfml/include
DEPENDPATH += $$PWD/sfml/include

unix:!mac{
  QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN
  QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/lib
  QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/libs
  QMAKE_LFLAGS_RPATH=
}
