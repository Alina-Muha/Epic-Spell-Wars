#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QJsonDocument>
#include<QJsonArray>
#include<QJsonObject>
#include<QJsonValue>

class JsonCard
{
public:
    JsonCard(QJsonObject jObj);
    QJsonObject toJsonObject();
private:
    QString type_of_spell;
    int number;
    bool need_to_roll_the_dice;
};

class CardsJsonController
{
public:
    CardsJsonController();
    QByteArray list();
    void append(QByteArray json);
    void clear();
private:
    QList<JsonCard> items;
};

class JsonMessage{
public:
private:

};

#endif // CONTROLLER_H
