TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    introstate.cpp \
    matchstate.cpp \
    statemanager.cpp \
    game.cpp \
    gamestate.cpp \
    gameentity.cpp

HEADERS += \
    gamestate.h \
    introstate.h \
    matchstate.h \
    statemanager.h \
    game.h \
    statechangetype.h \
    inttostring.h \
    gameentity.h

QMAKE_CXXFLAGS += -std=c++0x

OTHER_FILES += \
    SourceSansPro-Light.ttf \
    todo.txt


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/sfml-build/lib/release/ -lsfml-system
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/sfml-build/lib/debug/ -lsfml-system
else:unix: LIBS += -L$$PWD/sfml-build/lib/ -lsfml-system
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/sfml-build/lib/release/ -lsfml-window
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/sfml-build/lib/debug/ -lsfml-window
else:unix: LIBS += -L$$PWD/sfml-build/lib/ -lsfml-window
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/sfml-build/lib/release/ -lsfml-graphics
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/sfml-build/lib/debug/ -lsfml-graphics
else:unix: LIBS += -L$$PWD/sfml-build/lib/ -lsfml-graphics
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/sfml-build/lib/release/ -lsfml-audio
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/sfml-build/lib/debug/ -lsfml-audio
else:unix: LIBS += -L$$PWD/sfml-build/lib/ -lsfml-audio

INCLUDEPATH += $$PWD/sfml/include
DEPENDPATH += $$PWD/sfml/include

unix:!mac{
  QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN
  QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/lib
  QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/libs
  QMAKE_LFLAGS_RPATH=
}
