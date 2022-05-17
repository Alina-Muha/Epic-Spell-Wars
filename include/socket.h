#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <mutex>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#include <condition_variable>

namespace socket{

struct QueriesKeeper {
    std::queue<std::pair<std::string, QTcpSocket *>> parsed_queries;
    std::queue<std::pair<std::string, QTcpSocket *>> prepared_queries;
    std::condition_variable query_available;
    std::mutex queries_mutex;
};


class Socket : public QObject
{
    Q_OBJECT

protected:
    QueriesKeeper *keeper;
    QTcpServer *server;
    QList<QTcpSocket *> sockets;

public:
    explicit Socket(const QHostAddress &host,
                    quint16 port,
                    QueriesKeeper *keeper1,
                    QObject *parent = nullptr);

public slots:

    void read();
    void connect();
    void disconnect();
    void send();


};

class QueryProcessor : public QObject {
    Q_OBJECT
protected:
    QueriesKeeper *keeper;
    Socket &socket;
    std::vector<std::string> data;
    QTcpSocket *to;

public:
    explicit QueryProcessor(QueriesKeeper *keeper, Socket &socket);

    static std::vector<std::string> parse(const std::string &raw_data);

    void wait_next_query();

    virtual void process() = 0;

    void prepare_query(const std::string &q, QTcpSocket *cli);

signals:

    void prepared();
};


}  // namespace socket
#endif // SOCKET_H
