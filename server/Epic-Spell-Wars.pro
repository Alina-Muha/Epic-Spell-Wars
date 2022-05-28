# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = Epic-Spell-Wars

QT = core gui widgets
QT += network
QMAKE_CXXFLAGS += -std=c++17
QT += qml quick

HEADERS = \
   $$PWD/include/card.h \
   $$PWD/include/cards_functions.h \
   $$PWD/include/game.h \
   $$PWD/include/player.h \
   $$PWD/include/round.h \
   $$PWD/include/server.h \
   $$PWD/include/dice.h \
   $$PWD/../common/include/controller.h

SOURCES = \
   $$PWD/src/card.cpp \
   $$PWD/src/cards_functions.cpp \
   $$PWD/src/game.cpp \
   $$PWD/src/main.cpp \
   $$PWD/src/player.cpp \
   $$PWD/src/round.cpp \
   $$PWD/src/server.cpp \
   $$PWD/src/dice.cpp \
   $$PWD/../common/src/controller.cpp

INCLUDEPATH = \
    $$PWD/include \
    $$PWD/../common/include

#DEFINES =

