#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QComboBox>
#include <QTimer>

#include "titlebar.h"

#pragma execution_character_set("utf-8")

#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent), m_pHBoxLayout(NULL)
{
    setFixedHeight(66);
    setAttribute(Qt::WA_StyledBackground);

    QVBoxLayout* pVBoxLayout = new QVBoxLayout(this);
    m_pHBoxLayout = new QHBoxLayout();
    InitFunctionBtn(m_pHBoxLayout);
    m_pHBoxLayout->setContentsMargins(10, 0, 10, 0);
    pVBoxLayout->addLayout(m_pHBoxLayout);
    pVBoxLayout->addStretch(1);
}

TitleBar::~TitleBar()
{

}


void TitleBar::mousePressEvent(QMouseEvent *event)
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

bool TitleBar::eventFilter(QObject *obj, QEvent *event)
{
    return QWidget::eventFilter(obj, event);
}

void TitleBar::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if (pButton == m_pMinButton)
        {
           pWindow->showMinimized();
        }
//        else if (pButton == m_pMaxButton)
//        {
//           pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
//        }
        else if (pButton == m_pCloseButton)
        {
           pWindow->close();
        }
    }
}

void TitleBar::updateMaximize()
{
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        bool bMaximize = pWindow->isMaximized();
//        if (bMaximize)
//        {
//           m_pMaxButton->setToolTip(tr("Restore"));
//           m_pMaxButton->setProperty("maximizeProperty", "restore");
//        }
//        else
//        {
//           m_pMaxButton->setProperty("maximizeProperty", "maximize");
//           m_pMaxButton->setToolTip(tr("Maximize"));
//        }

//        m_pMaxButton->setStyle(QApplication::style());
    }
}

void TitleBar::InitMenuBtn(QHBoxLayout *pLayout)
{
  
}

void TitleBar::InitFunctionBtn(QHBoxLayout *pLayout)
{
    m_pMinButton = new QPushButton();
    m_pMinButton->setMaximumWidth(44);
    m_pMinButton->setStyleSheet("padding: 2px;border: none;background-image: url(:/image/min.png);background-repeat: no-repeat;background-position: center;");
    connect(m_pMinButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));

    m_pCloseButton = new QPushButton();
     m_pCloseButton->setMaximumWidth(44);
    m_pCloseButton->setStyleSheet("padding: 2px;border: none;background-image: url(:/image/close.png);background-repeat: no-repeat;background-position: center;");
    connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));

    m_title = new QLabel();
    m_title->setText("V2.30.0525");
    pLayout->addWidget(m_title);

    QPushButton* pTheme = new QPushButton("主题选择");
    connect(pTheme, &QPushButton::released, [this](){
        emit sigTheme();
    });

    pLayout->addWidget(pTheme);
    pLayout->addStretch(1);
    pLayout->addWidget(m_pMinButton);
    pLayout->addWidget(m_pCloseButton);
    pLayout->setSpacing(10);
}
