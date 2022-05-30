#include "board.h"
#include "ui_board.h"
#include <QTimer>

Board::Board(client::Client *client_, QWidget *parent) :
        QWidget(parent),
        client(client_),
        ui(new Ui::Board)
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Board::update_from_server);
    timer->start(1000);
    ui->setupUi(this);
}

void Board::update_from_server() {
    while (!client->requestsQueue.empty()) {
        auto request = client->requestsQueue.front();
        client->requestsQueue.pop_front();

        if (request.get_type() == 3) {

        }
        if (request.get_type() == 4) {
            qDebug() << QString("Got cards, size: %1").arg(request.get_cards()->size());
        }
    }
}

Board::~Board()
{
    delete ui;
}

void Board::on_pushButton_clicked()
{

}
