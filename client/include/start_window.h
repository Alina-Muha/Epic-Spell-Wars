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
    explicit Start_window(std::shared_ptr<client::Client> client_, QWidget *parent = nullptr);
    ~Start_window();

private slots:
            void on_start_button_clicked();           

            void on_registration_button_clicked();

            void name_duplicate();

            void successful_registration();

            void update_from_server();

private:
    std::shared_ptr<client::Client> client;
    Ui::Start_window *ui;
    std::shared_ptr<Board> b;

};
#endif // START_WINDOW_H
