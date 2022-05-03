#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
namespace server{
class server : public QObject{
    Q_OBJECT
public:
    explicit server(QObject *parent = nullptr);
public slots:
    void new_connection();
    void read_connection();
    void disconnection();
private:
    QTcpServer *tcp_server;
    QTcpSocket *tcp_socket;

};
} // namespace server

#endif // SERVER_H
