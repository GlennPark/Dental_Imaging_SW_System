/*
 * 프로그램명 : SubServer
 * 파일명 : subserver.h
 * 설명 : 영상 검사실용 미니 서버 (촬영SW와 Modality의 연결)
 * 작성자 : 안다미로
 * 최종 수정일 : 2023.01.06
 */

#ifndef SUBSERVER_H
#define SUBSERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QProgressDialog>

class Protocol;

QT_BEGIN_NAMESPACE
namespace Ui { class SubServer; }
QT_END_NAMESPACE

class SubServer : public QWidget
{
    Q_OBJECT

public:
    explicit SubServer(QWidget *parent = nullptr);
    ~SubServer();

private slots:
    void newClient();
    void newFileClient();
    void receiveControl();
    void firstFileSocket();
    void receiveFile();
    void sendFile();

private:
    Ui::SubServer *ui;

    QString currentPID = "NULL";
    QString currentType = "NULL";

    Protocol *protocol;

    QTcpServer *controlServer;
    QTcpServer *fileServer;
    QMap<QTcpSocket*, int> controlSocketMap;    // <socket, SW or MODALITY>
    QMap<QTcpSocket*, int> fileSocketMap;       // <socket, SW or MODALITY>

    QByteArray totalData;
};
#endif // SUBSERVER_H
