#include "board.h"
#include "ui_board.h"

Board::Board(client::Client *client_, QWidget *parent) :
        QWidget(parent),
        client(client_),
        ui(new Ui::Board)
{
    ui->setupUi(this);
}

Board::~Board()
{
    delete ui;
}

void Board::on_pushButton_clicked()
{

}
