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

QMAKE_CXXFLAGS += -std=c++0x

OTHER_FILES += \
    intro.svg \
    intro.png \
    SourceSansPro-Light.ttf \
    SourceSansPro-Light.ttf


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/sfml-build/lib/release/ -lsfml-system
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/sfml-build/lib/debug/ -lsfml-system
else:unix: LIBS += -L$$PWD/sfml-build/lib/ -lsfml-system
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/sfml-build/lib/release/ -lsfml-window
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/sfml-build/lib/debug/ -lsfml-window
else:unix: LIBS += -L$$PWD/sfml-build/lib/ -lsfml-window
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/sfml-build/lib/release/ -lsfml-graphics
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/sfml-build/lib/debug/ -lsfml-graphics
else:unix: LIBS += -L$$PWD/sfml-build/lib/ -lsfml-graphics

INCLUDEPATH += $$PWD/sfml/include
DEPENDPATH += $$PWD/sfml/include

unix:!mac{
  QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN
  QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/lib
  QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/libs
  QMAKE_RPATH=
}
