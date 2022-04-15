# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = Epic-Spell-Wars

QT = core gui widgets

HEADERS = \
   $$PWD/include/board.h \
   $$PWD/include/card.h \
   $$PWD/include/cards_functions.h \
   $$PWD/include/game.h \
   $$PWD/include/player.h \
   $$PWD/include/round.h \
   $$PWD/include/start_window.h

SOURCES = \
   $$PWD/src/board.cpp \
   $$PWD/src/card.cpp \
   $$PWD/src/cards_functions.cpp \
   $$PWD/src/game.cpp \
   $$PWD/src/main.cpp \
   $$PWD/src/player.cpp \
   $$PWD/src/round.cpp \
   $$PWD/src/start_window.cpp \
FORMS = \
   $$PWD/forms/board.ui \
   $$PWD/forms/start_window.ui \
INCLUDEPATH = \
    $$PWD/include

#DEFINES =

DISTFILES += \
    cards/Delivery_1.png \
    cards/Delivery_2.png \
    cards/Delivery_3.png \
    cards/Delivery_4.png \
    cards/Delivery_5.png \
    cards/Delivery_6.png \
    cards/Quality_1.png \
    cards/Quality_2.png \
    cards/Quality_3.png \
    cards/Quality_4.png \
    cards/Quality_5.png \
    cards/Quality_6.png \
    cards/Source_1.png \
    cards/Source_2.png \
    cards/Source_3.png \
    cards/Source_4.png \
    cards/Source_5.png \
    cards/Source_6.png

RESOURCES += \
    cards/start_window_background.qrc
