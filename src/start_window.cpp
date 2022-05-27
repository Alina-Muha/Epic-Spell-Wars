#include "ui_start_window.h"
#include "board.h"
#include "player.h"
#include "start_window.h"

Start_window::Start_window(QWidget *parent)
        : QWidget(parent)
        , ui(new Ui::Start_window),
          b(new Board())
{
    ui->setupUi(this);
}

Start_window::~Start_window()
{
    delete ui;
}


void Start_window::on_start_button_clicked()
{
    b->show();
    Start_window::close();
}


void Start_window::on_registration_button_clicked()
{
    std::string name;
    name = (ui->name_edit->text()).toStdString();
}


void Start_window::on_connect_button_clicked()
{
    ui->info_label->setText(
    "You are connected to the game, now enter the name");
}

void Start_window::name_duplicate() {
    ui->info_label->setText(
            "The name is already in use, please enter another one");
}

void Start_window::successful_registration(){
    ui->info_label->setText(
            "You are registered and can start the game");
}


/*
namespace Ui {
Start_window::Start_window(QWidget *parent)
        : QWidget(parent)
        , ui(new Ui::Start_window),
          b(new Board())
{
    ui->setupUi(this);
    //connect(socket, &QTcpSocket::readyRead, this, &Start_window::slotReadyRead);
    //connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
}

Start_window::~Start_window()
{
    delete ui;
}

void Start_window::on_start_button_clicked()
{
    //send_name_to_server(ui->lineEdit->text());
    b->show();
    Start_window::close();
}

void Start_window::on_connect_button_clicked()
{
    //socket->connectToHost("127.0.0.1", 2323);
}

void Start_window::send_name_to_server(QString name) {
    // TODO
}



void Start_window::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if (in.status() == QDataStream::Ok) {
        Qstring name;
        in >> name; // ????

    }
}
}

void Start_window::on_registration_button_clicked()
{

}
*/



