# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = Epic-Spell-Wars

QT = core gui widgets
QT += network
QMAKE_CXXFLAGS += -std=c++17
QT += qml quick

HEADERS = \
   $$PWD/include/board.h \
   $$PWD/include/card.h \
   $$PWD/include/cards_functions.h \
   $$PWD/include/game.h \
   $$PWD/include/player.h \
   $$PWD/include/round.h \
   $$PWD/include/start_window.h \
   $$PWD/include/server.h \
   $$PWD/include/client.h \
   $$PWD/include/dice.h \
   $$PWD/include/socket.h

SOURCES = \
   $$PWD/src/board.cpp \
   $$PWD/src/card.cpp \
   $$PWD/src/cards_functions.cpp \
   $$PWD/src/game.cpp \
   $$PWD/src/main.cpp \
   $$PWD/src/player.cpp \
   $$PWD/src/round.cpp \
   $$PWD/src/start_window.cpp \
   $$PWD/src/server.cpp \
   $$PWD/src/client.cpp \
   $$PWD/src/dice.cpp \
   $$PWD/src/socket.cpp

FORMS = \
   $$PWD/forms/board.ui \
   $$PWD/forms/start_window.ui

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
    cards/Delivery_7.png \
    cards/Delivery_8.png \
    cards/Delivery_9.png \
    cards/Delivery_10.png \
    cards/Delivery_11.png \
    cards/Delivery_12.png \
    cards/Delivery_13.png \
    cards/Delivery_14.png \
    cards/Quality_1.png \
    cards/Quality_11.png \
    cards/Quality_12.png \
    cards/Quality_13.png \
    cards/Quality_2.png \
    cards/Quality_3.png \
    cards/Quality_4.png \
    cards/Quality_5.png \
    cards/Quality_6.png \
    cards/Quality_7.png \
    cards/Quality_8.png \
    cards/Quality_9.png \
    cards/Quality_10.png \
    cards/Source_1.png \
    cards/Source_14.png \
    cards/Source_15.png \
    cards/Source_2.png \
    cards/Source_3.png \
    cards/Source_4.png \
    cards/Source_5.png \
    cards/Source_6.png \
    cards/Source_7.png \
    cards/Source_8.png \
    cards/Source_9.png \
    cards/Source_10.png \
    cards/Source_11.png \
    cards/Source_12.png \
    cards/Source_13.png

RESOURCES += \
    cards/start_window_background.qrc
