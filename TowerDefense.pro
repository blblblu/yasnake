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

INCLUDEPATH += $$PWD/sfml/include
DEPENDPATH += $$PWD/sfml/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/sfml-build/lib/release/ -lsfml-window
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/sfml-build/lib/debug/ -lsfml-window
else:unix: LIBS += -L$$PWD/sfml-build/lib/ -lsfml-window

INCLUDEPATH += $$PWD/sfml/include
DEPENDPATH += $$PWD/sfml/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/sfml-build/lib/release/ -lsfml-graphics
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/sfml-build/lib/debug/ -lsfml-graphics
else:unix: LIBS += -L$$PWD/sfml-build/lib/ -lsfml-graphics

INCLUDEPATH += $$PWD/sfml/include
DEPENDPATH += $$PWD/sfml/include
