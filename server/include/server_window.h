#ifndef SERVER_WINDOW_H
#define SERVER_WINDOW_H

#include <QWidget>
#include"server.h"

namespace Ui {
class server_window;
}

class server_window : public QWidget
{
    Q_OBJECT

public:
    explicit server_window(QWidget *parent = nullptr);
    ~server_window();

private slots:
    void on_send_clicked();

private:
    Ui::server_window *ui;
    std::shared_ptr<server::Server> play_server;
};

#endif // SERVER_WINDOW_H
