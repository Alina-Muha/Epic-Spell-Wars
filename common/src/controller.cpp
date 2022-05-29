#include "controller.h"
#include <QVariant>

#define F_TYPE "type_of_spell"
#define F_NUM "number"
#define F_NEED_TO_ROLL_THE_DICE "need_to_roll_the_dice"

JsonCard::JsonCard(QJsonObject jObj) {
    type_of_spell = jObj.value(F_TYPE).toString();
    number = jObj.value(F_NUM).toInt();

}

QJsonObject JsonCard::toJsonObject() {
    QJsonObject jObj;
    jObj.insert(F_TYPE, QJsonValue::fromVariant(type_of_spell));
    jObj.insert(F_NUM, QJsonValue::fromVariant(number));
    jObj.insert(F_NEED_TO_ROLL_THE_DICE, QJsonValue::fromVariant(need_to_roll_the_dice));
}

CardsJsonController::CardsJsonController(){

}
QByteArray CardsJsonController::list(){
   QJsonArray jCards;
   foreach (JsonCard card, items){
       jCards.append(card.toJsonObject());
   }
   return QJsonDocument(jCards).toJson();
}
void CardsJsonController::append(QByteArray json){
    QJsonObject jCard = QJsonDocument::fromJson(json).object();
    items.append(JsonCard(jCard));
}
void CardsJsonController::clear(){
    items.clear();
}
