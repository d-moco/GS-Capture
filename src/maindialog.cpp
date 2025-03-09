#include "maindialog.h"
#include "ui_maindialog.h"
#include "mainwidget.h"
#include "imagemanager.h"
#include "imageeditwidget.h"
#include "commonstylesheet.h"

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    m_titleBar = new MainTitleBar();
    connect(m_titleBar, &MainTitleBar::sigSwitchWnd, this, &MainDialog::onSwitchWindow);
    ui->horizontalLayout->addWidget(m_titleBar);

    onSwitchWindow(eMainWnd);

    refeshStyleSheet();
}


void MainDialog::refeshStyleSheet(EThemeColor clr)
{
    QString strColor = ComStyleSheet->getThemeClr() == eDrak ? DRAK_TITLE_BAR_FONT_COLOR : LIGHT_TITLE_BAR_FONT_COLOR;
    if (clr == eDrak) {
        this->setStyleSheet(""
        "QPushButton { padding: 2px;}"
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
    } else {
        this->setStyleSheet(
            "QPushButton { padding: 2px;}"
            "QToolButton { font-family: 'Microsoft YaHei'; background-color: #FFFFFF; color: #333333; border: 2px solid #CCCCCC; border-radius: 8px; padding: 6px; font-size: 18px; }"
            "QToolButton:hover { background-color: #F0F0F0; border: 2px solid #00CCFF; }"
            "QToolButton:pressed { background-color: #E0E0E0; border: 2px solid #00BBEE; }");
    }
}


MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::onSwitchWindow(EWindowType type)
{
    if (type == eReturnWnd) {
        onSwitchWindow(eMainWnd);
    } else {
        if (m_currentType != type) {
            QWidget* pwidget = nullptr;
            if (m_wndMap.count(type) > 0) {
                pwidget = m_wndMap[type];

                if (type == eMainWnd) {
                    m_titleBar->setReturnIsShow(false);
                    MainWidget* pWgt = (MainWidget*)m_wndMap[type];
                    pWgt->setWidgetType(eMainWnd);
                } else if (type == eSettingWnd) {
                    m_titleBar->setReturnIsShow(true);
                    MainWidget* pWgt = (MainWidget*)m_wndMap[type];
                    pWgt->setWidgetType(eSettingWnd);
                } else {
                    m_titleBar->setReturnIsShow(true);
                }
            }
            else {
                m_titleBar->setReturnIsShow(true);
                switch (type)
                {
                case eMainWnd:
                {
                    m_titleBar->setReturnIsShow(false);
                    if (m_wndMap.count(eSettingWnd) > 0) {
                        MainWidget* pWgt = (MainWidget*)m_wndMap[eSettingWnd];
                        pWgt->setWidgetType(eMainWnd);
                        pwidget = pWgt;
                    } else {
                        pwidget = new MainWidget(type);
                    }

                    break;
                }
                case eSettingWnd:
                {
                    if (m_wndMap.count(eMainWnd) > 0) {
                        MainWidget* pWgt = (MainWidget*)m_wndMap[eMainWnd];
                        pWgt->setWidgetType(eSettingWnd);
                        pwidget = pWgt;
                    } else {
                        pwidget = new MainWidget(type);
                    }

                    break;
                }
                case eImageMgrWnd:
                {
                    pwidget = new ImageManager();
                    connect((ImageManager*)pwidget, &ImageManager::sigOpenImageEdit, this, &MainDialog::onSwitchImageAndSetImage, Qt::QueuedConnection);
                    break;
                }
                case eImageEditWnd:
                {
                     pwidget = new ImageEditWidget();
                    break;
                }

                default:
                    break;
                }

                if (pwidget) {
                    m_wndMap[type] = pwidget;
                }
            }

            if (pwidget) {
                ui->widget->hide();
                ui->verticalLayout_login->removeWidget(ui->widget);
                ui->widget = pwidget;
                ui->verticalLayout_login->addWidget(ui->widget);
                ui->widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                ui->widget->show();

                m_currentType = type;
            }
        }
    }
}

void MainDialog::onSwitchImageAndSetImage(const QString& strPath)
{
    onSwitchWindow(eImageEditWnd);
    if (m_wndMap.count(eImageEditWnd) > 0) {
        ImageEditWidget* pWidget = (ImageEditWidget*)m_wndMap[eImageEditWnd];
        if (pWidget) {
            pWidget->switchImage(strPath);
        }
    }
}
