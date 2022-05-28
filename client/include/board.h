#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "../../server/include/client.h"

namespace Ui {
    class Board;
}

class Board : public QWidget
{
    Q_OBJECT

public:
    explicit Board(client::Client *client_ = nullptr, QWidget *parent = nullptr);
    ~Board();

private slots:
            void on_pushButton_clicked();

private:
            client::Client *client;
    Ui::Board *ui;
};

#endif // BOARD_H
