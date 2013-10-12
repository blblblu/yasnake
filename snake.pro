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
    player.cpp \
    pausestate.cpp \
    scorestate.cpp

HEADERS += \
    debugoutput.hpp \
    game.hpp \
    gamestate.hpp \
    matchstate.hpp \
    menustate.hpp \
    player.hpp \
    statemanager.hpp \
    stateevent.hpp \
    direction.hpp \
    pausestate.hpp \
    scorestate.hpp

QMAKE_CXXFLAGS += -std=c++0x

OTHER_FILES += \
    SourceSansPro-Light.ttf \
    todo.txt \
    Farbcodes.txt

unix:!macx:!symbian: LIBS += -L$$PWD/sfml-build/lib/ -lsfml-system
unix:!macx:!symbian: LIBS += -L$$PWD/sfml-build/lib/ -lsfml-window
unix:!macx:!symbian: LIBS += -L$$PWD/sfml-build/lib/ -lsfml-graphics


INCLUDEPATH += $$PWD/sfml/include
DEPENDPATH += $$PWD/sfml/include

unix:!mac{
  QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN
  QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/lib
  QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/libs
  QMAKE_LFLAGS_RPATH=
}

INCLUDEPATH += $$PWD/boost_1_54_0



win32: LIBS += -L$$PWD/sfml-build/lib/ -lsfml-main -lsfml-system -lsfml-window -lsfml-graphics

