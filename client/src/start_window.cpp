#include "ui_start_window.h"
#include "client.h"
#include "board.h"
#include "start_window.h"
#include <QDebug>
#include <QTimer>

Start_window::Start_window(client::Client* client_, QWidget *parent)
        : QWidget(parent),
          ui(new Ui::Start_window),
          b(new Board(client_))
{
    client = client_;
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Start_window::update_from_server);
    timer->start(1000);
    ui->setupUi(this);
}

Start_window::~Start_window()
{
    delete ui;
}


void Start_window::on_start_button_clicked()
{
    client->send_start_signal();
}

void Start_window::update_from_server() {
    qDebug() << "name " << client->get_name();
    qDebug() << "update_from_server"<< client->requestsQueue.size()<< "\n";
    while (!client->requestsQueue.empty()) {
        qDebug() << "in while\n";
        auto request = client->requestsQueue.front();
        client->requestsQueue.pop_front();
        qDebug() << request.get_type() << "\n";
        if (request.get_type() == 2) {
            qDebug() <<  "snons";
            b->show();
            Start_window::close();
            break;
        }
    }
}



void Start_window::on_registration_button_clicked()
{
    std::string name;
    client->set_name((ui->name_edit->text()));
    client->connect();
    // if registration is successfull
    successful_registration();
}


void Start_window::name_duplicate() {
    ui->info_label->setText(
            "The name is already in use, please enter another one");
}

void Start_window::successful_registration(){
    ui->info_label->setText(
            "You are registered. Push START button when other players will be ready");
}




