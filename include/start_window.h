#ifndef START_WINDOW_H
#define START_WINDOW_H

#include "board.h"
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
    explicit Start_window(QWidget *parent = nullptr);
    ~Start_window();

private slots:
            void on_start_button_clicked();

            void on_connect_button_clicked();

            void send_name_to_server(QString name);

private:
    Ui::Start_window *ui;
    Board* b;
    QTcpSocket *socket;
    QByteArray Data;

public slots:
    void slotReadyRead();
};
#endif // START_WINDOW_H
