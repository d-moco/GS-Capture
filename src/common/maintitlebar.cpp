#include "maintitlebar.h"
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QToolButton>

#pragma execution_character_set("utf-8")

#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

MainTitleBar::MainTitleBar(QWidget *parent)
    : QWidget{parent}
{
    setFixedHeight(60);
    setAttribute(Qt::WA_StyledBackground);

    m_pHBoxLayout = new QHBoxLayout(this);
    InitFunctionBtn(m_pHBoxLayout);
    m_pHBoxLayout->setContentsMargins(10, 0, 10, 0);
}

void MainTitleBar::mousePressEvent(QMouseEvent *event)
{
#ifdef Q_OS_WIN
    if (ReleaseCapture())
    {
        QWidget *pWindow = this->window();
        if (pWindow->isTopLevel())
        {
            SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
        }
    }
    event->ignore();
#else
#endif
}

bool MainTitleBar::eventFilter(QObject *obj, QEvent *event)
{
    return QWidget::eventFilter(obj, event);
}

void MainTitleBar::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if (pButton == m_pMinButton)
        {
            pWindow->showMinimized();
        }
        else if (pButton == m_pMaxButton)
        {
            bool bMax = pWindow->isMaximized();
            if (bMax) {
                pWindow->showNormal();
                m_pMaxButton->setStyleSheet("padding: 2px;border: none;background-image: url(:/image/max.png);background-repeat: no-repeat;background-position: center;");
            } else {
                pWindow->showMaximized();
                m_pMaxButton->setStyleSheet("padding: 2px;border: none;background-image: url(:/image/restore.png);background-repeat: no-repeat;background-position: center;");
            }

           //pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
        }
        else if (pButton == m_pCloseButton)
        {
            pWindow->close();
        }
    }
}

void MainTitleBar::InitFunctionBtn(QHBoxLayout *pLayout)
{
    m_pMinButton = new QPushButton();
    m_pMinButton->setMaximumWidth(44);
    m_pMinButton->setStyleSheet("padding: 2px; border: none;background-image: url(:/image/min.png);background-repeat: no-repeat;background-position: center;");
    connect(m_pMinButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));

    m_pMaxButton = new QPushButton();
    m_pMaxButton->setMaximumWidth(44);
    m_pMaxButton->setStyleSheet("padding: 2px;border: none;background-image: url(:/image/max.png);background-repeat: no-repeat;background-position: center;");
    connect(m_pMaxButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));

    m_pCloseButton = new QPushButton();
    m_pCloseButton->setMaximumWidth(44);
    m_pCloseButton->setStyleSheet("padding: 2px;border: none;background-image: url(:/image/close.png);background-repeat: no-repeat;background-position: center;");
    connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));

    m_pWndBtn = new QPushButton();
    m_pWndBtn->setMaximumWidth(44);
    m_pWndBtn->setStyleSheet("padding: 2px;border: none;background-image: url(:/image/windows.png);background-repeat: no-repeat;background-position: center;");
    //connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));

//    m_title = new QLabel();
//    m_title->setText("RGB设置");
//    pLayout->addWidget(m_title);

    m_return = new QToolButton();
    m_return->setMinimumHeight(40);
    m_return->setText("返回");
    m_return->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_return->setIcon(QIcon(":/image/return.png"));
    m_return->setIconSize(QSize(32, 32));

    QString strColor = "#1296db";
    this->setStyleSheet(
        "QToolButton "
        "{"
            "font-family: 'Microsoft YaHei';"
            "background-color: #333; "
            "color: " + strColor + ";"
             "border: 2px;"
             "border-radius: 8px;"
             "padding: 6px;"
             "font-size: 18px;"
        "}"
        "QToolButton:hover "
        "{"
             "background-color: #444;"
             "border: 2px solid #00CCFF;"
         "}"
         "QToolButton:pressed "
         "{"
             "background-color: #222;"
             "border: 2px solid #00BBEE;"
         "}");

    pLayout->addWidget(m_return);
    connect(m_return, &QToolButton::released, this, [=](){
        emit sigSwitchWnd(eReturnWnd);
    });

    pLayout->addStretch(1);

    m_temp = new QLabel();
    m_temp->setText("温度无");
    pLayout->addWidget(m_temp);

    m_camera = new QToolButton();
    m_camera->setMinimumHeight(40);
    m_camera->setText("相机");
    m_camera->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_camera->setIcon(QIcon(":/image/camera.png"));
    m_camera->setIconSize(QSize(32, 32));
    pLayout->addWidget(m_camera);

    m_imgMgr = new QToolButton();
    connect(m_imgMgr, &QToolButton::released, this, [=](){
        emit sigSwitchWnd(eImageMgrWnd);
    });
    m_imgMgr->setMinimumHeight(40);
    m_imgMgr->setText("图像管理");
    m_imgMgr->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_imgMgr->setIcon(QIcon(":/image/image.png"));
    m_imgMgr->setIconSize(QSize(32, 32));
    pLayout->addWidget(m_imgMgr);

    m_setting = new QToolButton();
    connect(m_setting, &QToolButton::released, this, [=](){
        emit sigSwitchWnd(eSettingWnd);
    });
    m_setting->setMinimumHeight(40);
    m_setting->setText("设置");
    m_setting->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_setting->setIcon(QIcon(":/image/setting.png"));
    m_setting->setIconSize(QSize(32, 32));
    pLayout->addWidget(m_setting);

    m_imgEdit = new QToolButton();
    connect(m_imgEdit, &QToolButton::released, this, [=](){
        emit sigSwitchWnd(eImageEditWnd);
    });
    m_imgEdit->setMinimumHeight(40);
    m_imgEdit->setText("图像编辑");
    m_imgEdit->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_imgEdit->setIcon(QIcon(":/image/imgedit.png"));
    m_imgEdit->setIconSize(QSize(32, 32));
    pLayout->addWidget(m_imgEdit);

    pLayout->addStretch(1);

    pLayout->addWidget(m_pWndBtn);
    pLayout->addWidget(m_pMinButton);
    pLayout->addWidget(m_pMaxButton);
    pLayout->addWidget(m_pCloseButton);
    pLayout->setSpacing(10);
}

void MainTitleBar::setReturnIsShow(const bool bShow)
{
    if (m_return) {
        m_return->setVisible(bShow);
    }
}
