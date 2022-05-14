#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QMap>
namespace server{
class server : public QObject{
    Q_OBJECT
public:
    explicit server(QObject *parent = nullptr);
    QString get_client(const QTcpSocket *client) const;
public slots:
    void new_connection();
    void read_connection();
    void disconnection();
    int get_cube_value();
private:
    QTcpServer *tcp_server;
    QMap<QString, QTcpSocket*> clients;

};
} // namespace server

#endif // SERVER_H
