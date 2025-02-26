#include "imageviewtoolwidget.h"
#include <QHBoxLayout>

ImageViewToolWidget::ImageViewToolWidget(QWidget *parent)
    : QWidget{parent}
{
    setAttribute(Qt::WA_TranslucentBackground); // 设置背景透明
    setWindowFlags(Qt::FramelessWindowHint); // 去掉窗口边框
    init();
}

void ImageViewToolWidget::init()
{
    this->setStyleSheet("QPushButton { padding: 2px;}"
                        "QToolButton {"
                        "background-color: #404040; color: #00FFCC;"
                        "border: 2px;"
                        "border-radius: 8px;"
                        "padding: 6px;"
                        "font-size: 16px;"
                        "min-width: 20px;"
                        "min-height: 20px;"
                        "}"
                        "QToolButton:hover {"
                        "background-color: #444;"
                        "border: 2px solid #00CCFF;"
                        "}"
                        "QToolButton:pressed {"
                        "background-color: #222;"
                        "border: 2px solid #00BBEE;"
                        "}" );


    QHBoxLayout* pHBox = new QHBoxLayout(this);

    m_pAdd = new QToolButton();
    m_pAdd->setIcon(QIcon(":/image/add.png"));
    m_pAdd->setIconSize(QSize(32,32));
    connect(m_pAdd, &QToolButton::released, [=](){
        emit sigImageOper(eAddImg);
    });

    m_pZoomIn = new QToolButton();
    m_pZoomIn->setIcon(QIcon(":/image/zoomin.png"));
    m_pZoomIn->setIconSize(QSize(32,32));
    connect(m_pZoomIn, &QToolButton::released, [=](){
        emit sigImageOper(eZoomInImg);
    });


    m_pZoomOut = new QToolButton();
    m_pZoomOut->setIcon(QIcon(":/image/zoomout.png"));
    m_pZoomOut->setIconSize(QSize(32,32));
    connect(m_pZoomOut, &QToolButton::released, [=](){
        emit sigImageOper(eZoomOutImg);
    });

    m_pReset = new QToolButton();
    m_pReset->setIcon(QIcon(":/image/autosize.png"));
    m_pReset->setIconSize(QSize(32,32));
    connect(m_pReset, &QToolButton::released, [=](){
        emit sigImageOper(eResetImg);
    });

    m_pDeleteImage = new QToolButton();
    m_pDeleteImage->setIcon(QIcon(":/image/delete.png"));
    m_pDeleteImage->setIconSize(QSize(32,32));
    connect(m_pDeleteImage, &QToolButton::released, [=](){
        emit sigImageOper(eDeleteImg);
    });

    pHBox->addStretch(1);

    pHBox->addWidget(m_pAdd);
    pHBox->addWidget(m_pZoomIn);
    pHBox->addWidget(m_pReset);
    pHBox->addWidget(m_pZoomOut);
    pHBox->addWidget(m_pDeleteImage);

     pHBox->addStretch(1);

    this->setMinimumHeight(30);
}
