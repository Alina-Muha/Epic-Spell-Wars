#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QMap>
namespace server{
class Server : public QObject{
    Q_OBJECT
    Q_DISABLE_COPY(Server)
public:
    explicit Server(QObject *parent = nullptr);
    virtual bool set_socket_descriptor(qintptr socket_descriptor);
    QString user_name() const;
    void set_user_name(const QString &user_name);
    void send_json(const QJsonObject &json_data);
signals:
    void json_received(const QJsonObject &json_doc);
    void disconnected_from_client();
    void error();
    void log_message (const QString &msg);
public slots:
    void disconnect_from_client();
private slots:
    void receive_json();
private:
    QTcpSocket *m_server_socket;
    QString m_user_name;

};
} // namespace server

#endif // SERVER_H
