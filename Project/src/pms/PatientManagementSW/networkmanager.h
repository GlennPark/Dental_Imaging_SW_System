#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QtCore>
#include <QtNetwork>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    NetworkManager(QObject *parent = nullptr);

public slots:
    bool connectToMainHost(QString host);
    bool connectToFileHost(QString host);
    bool writeData(QByteArray data);

private slots:
    void newDataSended(QString);

    void receiveData();
    void receiveFile();
//    void newConnection();
//    void disconnected();

private:
    QTcpSocket *socket;
    bool fd_flag = false;
    bool file_flag = false;
    bool send_flag = false;
    QTcpSocket *PMSocket;
    QByteArray *buffer;
    QString saveData;

    QString sendedPID;
    QHash<QTcpSocket*, QByteArray*> buffers; //We need a buffer to store data until block has completely received
    QTcpServer *server;
    QHash<QTcpSocket*, qint32*> sizes; //We need to store the size to verify if a block has received completely



    QTcpSocket *fileSocket;
    qint64 totalSize;
    qint64 byteReceived = 0;
    QString fileName;                           // Receiving FileName
    QString checkFileName;
    QFile* file;
    QByteArray inBlock;
    QString currentPID = "NULL";

signals:
    void sendNewPID(QString);
    void sendSearchResult(QString, QString);
    void sendSRQRequest(QString);
    void sendVTSRequest(QString);
    void sendISVevent(QString);
    void sendVTFevent(QString);




};

#endif // NETWORKMANAGER_H
