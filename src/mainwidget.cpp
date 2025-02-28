#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDebug>

MainWidget::MainWidget(EWindowType type, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    if (type == eMainWnd) {
        ui->frame_seting->setVisible(false);
    } else if (type == eSettingWnd) {
        ui->frame_seting->setVisible(true);
    }

    initStyleSheet();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::setWidgetType(EWindowType type)
{
    if (type == eMainWnd) {
        ui->frame_seting->setVisible(false);
    } else if (type == eSettingWnd) {
        ui->frame_seting->setVisible(true);
    }
 }

void MainWidget::initStyleSheet()
{
    this->setStyleSheet("QPushButton { padding: 2px;}"
                        "QToolButton {"
                        "background-color: #404040; color: #00FFCC;"
                        "border: 2px;"
                        "border-radius: 8px;"
                        "padding: 6px;"
                        "font-size: 16px;"
                        "}"
                        "QToolButton:hover {"
                        "background-color: #444;"
                        "border: 2px solid #00CCFF;"
                        "}"
                        "QToolButton:pressed {"
                        "background-color: #222;"
                        "border: 2px solid #00BBEE;"
                        "}" );

    ui->btn_select->setMinimumHeight(40);
    ui->btn_select->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->btn_select->setIconSize(QSize(32, 32));
//    ui->btn_select->setStyleSheet(
//        "QToolButton {"
//        "background-color: #333; color: #00FFCC;"
//        "border: 2px;"
//        "border-radius: 8px;"
//        "padding: 6px;"
//        "font-size: 16px;"
//        "}"
//        "QToolButton:hover {"
//        "background-color: #444;"
//        "border: 2px solid #00CCFF;"
//        "}"
//        "QToolButton:pressed {"
//        "background-color: #222;"
//        "border: 2px solid #00BBEE;"
//        "}"
//        );

    ui->add->setText("+");
    ui->sub->setText("-");
    ui->f1->setText("F0.95");
    ui->f2->setText("F16");

    ui->chb_zfp->SetText("关闭");
    ui->chb_txhb->SetText("关闭");
    ui->chb_zdwc->SetText("关闭");

    connect(ui->chb_zfp, &SwitchButtonInside::Clicked, [=](bool status){
        ui->chb_zfp->SetStatus(status);
        ui->chb_zfp->SetText(status == true ? "开启":"关闭");
    });

    connect(ui->chb_txhb, &SwitchButtonInside::Clicked, [=](bool status){
        ui->chb_txhb->SetStatus(status);
        ui->chb_txhb->SetText(status == true ? "开启":"关闭");

    });

    connect(ui->chb_zdwc, &SwitchButtonInside::Clicked, [=](bool status){
        ui->chb_zdwc->SetStatus(status);
        ui->chb_zdwc->SetText(status == true ? "开启":"关闭");
    });
}
