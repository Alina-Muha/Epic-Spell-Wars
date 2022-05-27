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


#endif // CONTROLLER_H
