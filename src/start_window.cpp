#include "start_window.h"
#include "ui_start_window.h"
#include "board.h"

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


