﻿#include "cbctrawimageviewer.h"
#include <QFile>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtWidgets>
#include <QTimer>
#include <QPixmap>
#include <QDebug>


#define update_image();

CBCTRawImageViewer::CBCTRawImageViewer()
{
    QString panoFolder = "C:/Qt_VTK_CT/build/Debug/Pano_Frame(1152x64)";
    panoImageIterator = new QDirIterator(panoFolder, QDirIterator::Subdirectories);
    panoImageTimer = new QTimer(this);
    connect(panoImageTimer, &QTimer::timeout, this, &CBCTRawImageViewer::timeoutPanoTimer);

    QString cephFolder = "C:/Qt_VTK_CT/build/Debug/Ceph_Frame(48x2400)";
    cephImageIterator = new QDirIterator(cephFolder, QDirIterator::Subdirectories);
    cephImageTimer = new QTimer(this);
    connect(cephImageTimer, &QTimer::timeout, this, &CBCTRawImageViewer::timeoutCephTimer);
}



QPixmap CBCTRawImageViewer::PanoImageViewer()
{
//    QString panoPath = "C:/Qt_VTK_CT/build/Debug/Pano_Frame(1152x64)/0001.raw";
//    QFile panoFile(panoPath);
//    if (!panoFile.open(QFile::ReadOnly))
//        return QPixmap();
//    //int PanoNum = 1249;
//    QByteArray ba = panoFile.readAll();
//    const uchar* data = (const uchar*) ba.constData();;
//    panoFile.close();
//    //QImage image(data, 30, 30, QImage::Format_RGB32);
//    QImage* panoImage = new QImage(data, 150, 470, QImage::Format_RGB555);
//    QImage pano_Image(*panoImage);
//    QPixmap panoPix;
//    panoPix = QPixmap::fromImage(pano_Image,Qt::AutoColor);
//    return panoPix;
    return QPixmap();
}

QPixmap CBCTRawImageViewer::CephImageViewer()
{
//    QString folder = "C:/Qt_VTK_CT/build/Debug/Pano_Frame(1152x64)/0001.raw";
//    cephImageIterator = new QDirIterator(folder, QDirIterator::Subdirectories);

//    cephImageTimer = new QTimer(this);
//    connect(cephImageTimer, &QTimer::timeout, this, &CBCTRawImageViewer::ShowNextCephImage);
//    cephImageTimer->start(10);

//    if (cephImageIterator->hasNext())
//    {
//        cephImageIterator->next();

//        qDebug() << __FUNCTION__ << cephImageIterator->filePath();

//       // QPixmap panoPix = PanoImageViewer(cephImageIterator->filePath());
//        QPixmap cephPix(cephImageIterator->filePath());
//        return cephPix;
//    }
//    else
//    {
//        //imageIterator->rewind();
//    }
    return QPixmap();
}


void CBCTRawImageViewer::startPanoTimer()
{
    qDebug() << __FUNCTION__;
    // 타이머 시작
    panoImageTimer->start(10);
}

void CBCTRawImageViewer::startCephTimer()
{
    qDebug() << __FUNCTION__;
    // 타이머 시작
    cephImageTimer->start(10);
}

void CBCTRawImageViewer::stopPanoTimer()
{
    // 타이머 종료
    qDebug() << __FUNCTION__;
    panoImageTimer->stop();
}

void CBCTRawImageViewer::stopCephTimer()
{
    // 타이머 종료
    qDebug() << __FUNCTION__;
    cephImageTimer->stop();
}

void CBCTRawImageViewer::timeoutPanoTimer()
{
    // 타이머 함수 -> mainwindow로 이미지 파일 하나씩 읽어 보내주도록 한다.
    if (panoImageIterator->hasNext())
    {
        panoImageIterator->next();

        QString panoPath = panoImageIterator->filePath();

        qDebug() << __FUNCTION__ << panoPath;

        QFile panoFile(panoPath);
        if (!panoFile.open(QFile::ReadOnly))
            return;
        QByteArray pBa = panoFile.readAll();
        const uchar* pData = (const uchar*) pBa.constData();;
        panoFile.close();
        QImage* panoImage = new QImage(pData, 500, 150, QImage::Format_RGB555);

        emit signals_panoImage(panoImage);      // mainwindow 로 보내준다
    }
    else
    {
        //imageIterator->rewind();
    }
}

void CBCTRawImageViewer::timeoutCephTimer()
{
    // 타이머 함수 -> mainwindow로 이미지 파일 하나씩 읽어 보내주도록 한다.
    if (cephImageIterator->hasNext())
    {
        cephImageIterator->next();

        QString cephPath = cephImageIterator->filePath();

        qDebug() << __FUNCTION__ << cephPath;

        QFile cephFile(cephPath);
        if (!cephFile.open(QFile::ReadOnly))
            return;
        QByteArray cBa = cephFile.readAll();
        const uchar* cData = (const uchar*) cBa.constData();;
        cephFile.close();
//        QImage* cephImage = new QImage(cData, 150, 470, QImage::Format_Grayscale16);
        QImage* cephImage = new QImage(cData, 150, 500, QImage::Format_RGB555);

        emit signals_cephImage(cephImage);      // mainwindow 로 보내준다
    }
    else
    {
        //imageIterator->rewind();
    }
}

CBCTRawImageViewer::~CBCTRawImageViewer()
{

}
