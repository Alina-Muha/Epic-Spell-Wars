#ifndef START_WINDOW_H
#define START_WINDOW_H

#include "board.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Start_window; }
QT_END_NAMESPACE

class Start_window : public QWidget
{
    Q_OBJECT

public:
    Start_window(QWidget *parent = nullptr);
    ~Start_window();

private slots:
            void on_start_button_clicked();

private:
    Ui::Start_window *ui;
    Board* b;
};
#endif // START_WINDOW_H