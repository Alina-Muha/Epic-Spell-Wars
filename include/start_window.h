#ifndef START_WINDOW_H
#define START_WINDOW_H
#include "board.h"
#include "client.h"
#include <QWidget>
#include <QMainWindow>
#include <QTcpSocket>


QT_BEGIN_NAMESPACE
namespace Ui { class Start_window; }
QT_END_NAMESPACE

class Start_window : public QWidget
{
    Q_OBJECT

public:
    explicit Start_window(client::Client *client_ = nullptr, QWidget *parent = nullptr);
    ~Start_window();

private slots:
            void on_start_button_clicked();           

            void on_registration_button_clicked();

            void on_connect_button_clicked();

            void name_duplicate();

            void successful_registration();

            void send_name_to_server(std::string name);

private:
    client::Client *client;
    Ui::Start_window *ui;
    Board* b;

    // QTcpSocket *socket;
    // QByteArray Data;


public slots:
   // void slotReadyRead();
};
#endif // START_WINDOW_H
