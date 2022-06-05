#include <QDebug>
#include "server_window.h"
#include "ui_server_window.h"

server_window::server_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::server_window)
{
    ui->setupUi(this);

}

server_window::~server_window()
{
    delete ui;
}

void server_window::on_send_clicked()
{
    qint16 port = (ui->port->text()).toInt();
    ui->port->clear();
    play_server = std::make_shared<server::Server>(port);
    ui->info->setText("You are listening on a port" + QString::fromStdString(std::to_string(port)));
}

