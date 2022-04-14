#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
namespace server {
    class server : public QTcpServer {
        Q_OBJECT
    public:
        server(QObject *parent = nullptr);
        ~server();
        QTcpServer *mTcpServer;
        QTcpSocket *mTcpSocket;
    public slots:

        void create_user();

        void connect_user(int user);

        void read_user();

        void disconnect_user();
    };
}
#endif // SERVER_H