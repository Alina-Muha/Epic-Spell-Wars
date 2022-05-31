# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = test_card_functions

QT = core gui widgets
QT += network

HEADERS = \
   $$PWD/server/include/card.h \
   $$PWD/server/include/cards_functions.h \
   $$PWD/server/include/dice.h \
   $$PWD/server/include/game.h \
   $$PWD/server/include/player.h \
   $$PWD/server/include/round.h \

SOURCES = \
   $$PWD/server/src/card.cpp \
   $$PWD/server/src/cards_functions.cpp \
   $$PWD/server/src/dice.cpp \
   $$PWD/server/src/game.cpp \
   $$PWD/server/src/main.cpp \
   $$PWD/server/src/player.cpp \
   $$PWD/server/src/round.cpp \

INCLUDEPATH = \
    $$PWD/server/include

#DEFINES = 

