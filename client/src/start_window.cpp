#include "start_window.h"
using namespace controller;

Start_window::Start_window(std::shared_ptr<client::Client> client_,
                           QWidget *parent)
    : QWidget(parent), ui(new Ui::Start_window) {
  client = client_;
  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &Start_window::update_from_server);
  timer->start(500);
  ui->setupUi(this);
}

Start_window::~Start_window() { delete ui; }

void Start_window::on_start_button_clicked() { client->send_start_signal(); }

void Start_window::update_from_server() {
  if (!client->is_game_started()) {
    while (!client->requestsQueue.empty()) {
      auto request = client->requestsQueue.front();
      client->requestsQueue.pop_front();
      if (request.get_type() == types::start) {
        client->set_game_started_flag();
        b = std::make_shared<Board>(client);
        b->setWindowTitle("Epic spell wars of the battle wizards");
        b->show();
        Start_window::close();
        break;
      }
      else if (request.get_type() == types::registered) {
          successful_registration();
      } else if (request.get_type() == types::duplicate) {
          name_duplicate();
      } else if (request.get_type() == types::connected) {
          successful_connection();
      }
    }
  }
}

void Start_window::on_registration_button_clicked() {
  std::string name;
  client->set_name((ui->name_edit->text()));
  client->send_name();
}

void Start_window::name_duplicate() {
  ui->info_label->setText(
      " The name is already in use, please enter another one");
}

void Start_window::successful_registration() {
  ui->info_label->setText(" You are registered. Push START button when other "
                          "players will be ready");
}

void Start_window::successful_connection() {
    ui->info_label->setText("You are connected. Now register");
}

void Start_window::on_connect_button_clicked() {
  QString ip = ui->ip->text();
  qint16 port = ui->port->text().toInt();
  client->connect(ip, port);
}
