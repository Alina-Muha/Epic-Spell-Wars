#include "start_window.h"
#include "ui_start_window.h"
#include "board.h"
#include "player.h"

Start_window::Start_window(QWidget *parent)
        : QWidget(parent)
        , ui(new Ui::Start_window),
          b(new Board())
{
    ui->setupUi(this);
    connect(socket, &QTcpSocket::readyRead, this, &Start_window::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
}

Start_window::~Start_window()
{
    delete ui;
}

void Start_window::on_connect_button_clicked()
{
    socket->connectToHost("127.0.0.1", 2323);
}

void Start_window::send_name_to_server(QString name) {

}

void Start_window::on_start_button_clicked()
{
    send_name_to_server(ui->lineEdit->text());
    b->show();
    Start_window::close();
}

void Start_window::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if (in.status() == QDataStream::Ok) {
        Qstring name;
        in >> name;

    }
}





