#include "basedialog.h"
#include "ui_basedialog.h"
#include "titlebar.h"
#include <qdrawutil.h>
#include <QHBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QCheckBox>
#include <QListView>
#include <QGraphicsDropShadowEffect>
#include <QtMath>
#include <QDebug>
#include "sigslotmgr.h"

#include "maindialog.h"

#define _STR(x) #x
#define STRINGIFY(x)  _STR(x)

#pragma execution_character_set("utf-8")

BaseDialog::BaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BaseDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    initWidget();
    initTheme();

    refeshStyleSheet(ComStyleSheet->getThemeClr());
    connect(this, &BaseDialog::sigChangeTheme, SigSlotMgr::inst(), &SigSlotMgr::sigChangeTheme);
}

BaseDialog::~BaseDialog()
{
    delete ui;
}

void BaseDialog::initTheme()
{
    // win11下需要使用绝对路径
    //QString AppDir = qApp->applicationDirPath();
    //QString StylesDir = AppDir + "/styles";

    QString StylesDir = STRINGIFY(STYLES_DIR);
    m_customStyleSheet = new qcss::QtCustomStylesheet(this);
    m_customStyleSheet->setStylesDirPath(StylesDir);
    m_customStyleSheet->setCurrentStyle("qt_material");
    m_customStyleSheet->setDefaultTheme();
    m_customStyleSheet->updateStylesheet();
    qApp->setStyleSheet(m_customStyleSheet->styleSheet());
    connect(m_customStyleSheet, SIGNAL(stylesheetChanged()), this,
            SLOT(onStyleManagerStylesheetChanged()));
}

void BaseDialog::initWidget()
{
    m_titleBar = new TitleBar();

    connect(m_titleBar, &TitleBar::sigTheme, [=](){
        ThemeSet set(m_customStyleSheet);
        set.exec();
    });
    ui->horizontalLayout->addWidget(m_titleBar);

    initToolButton();

    connect( ui->btn_hsjcx, &QToolButton::released, this, [=](){
        //this->hide();
        MainDialog main;
        main.exec();
    });
}

void BaseDialog::onStyleManagerStylesheetChanged()
{
    QString str = m_customStyleSheet->currentTheme();
    if (str.contains("light_")) {
        ComStyleSheet->setThemeClr(eLight);
    } else {
        ComStyleSheet->setThemeClr(eDrak);
    }

    qApp->setStyleSheet(m_customStyleSheet->styleSheet());
    refeshStyleSheet(ComStyleSheet->getThemeClr());

    emit sigChangeTheme(ComStyleSheet->getThemeClr());
}

void BaseDialog::initToolButton()
{
    connect(ui->btn_hsjcx, &QToolButton::released, this, [=](){

    });
}

void BaseDialog::refeshStyleSheet(EThemeColor clr) {
    if (clr == eDrak) {
        this->setStyleSheet(
            "QToolButton {"
            "   background-color: #2c3e50;" // 深色背景
            "   border: none;"
            "   border-radius: 10px;"
            "   padding: 10px;"
            "   margin: 4px;"
            "   font-size:16px;"
            "   color: #ecf0f1;"
            "}"
            "QToolButton:hover {"
            "   background-color: #34495e;" // 稍微变亮一点的深色背景
            "   border: 2px solid #3498db;" // 科技蓝边框
            "}"
            "QToolButton:pressed {"
            "   background-color: #ecf0f1;" // 浅色背景，模拟按下效果
            "   color: #2c3e50;" // 文字颜色变为深色
            "   border: 2px solid #e74c3c;" // 警告红边框，增加对比度
            "}"
            "QToolButton:disabled {"
            "   background-color: #bdc3c7;" // 灰色背景表示禁用状态
            "   color: #ecf0f1;"
            "}"
        );
    } else {
        this->setStyleSheet(
            "QToolButton {"
            "    background-color: #ecf0f1;" /* 浅色背景 */
            "    border: none;"
            "    border-radius: 10px;"
            "    padding: 10px;"
            "    margin: 4px;"
            "    font-size: 16px;"
            "    color: #2c3e50;" /* 深色文字 */
            "}"
            "QToolButton:hover {"
            "    background-color: #dfe4ea;" /* 稍微变暗一点的浅色背景 */
            "    border: 2px solid #3498db;" /* 科技蓝边框 */
            "}"
            "QToolButton:pressed {"
            "    background-color: #bdc3c7;" /* 更浅的灰色背景，作为按下效果 */
            "    color: #566573;" /* 更深的文字颜色 */
            "    border: 2px solid #e74c3c;" /* 警告红边框，增加对比度 */
            "}"
            "QToolButton:disabled {"
            "    background-color: #bdc3c7;" /* 更浅的灰色背景表示禁用状态 */
            "    color: #ecf0f1;" /* 或者选择更浅的颜色以确保与背景对比度良好 */
            "}");
    }
}

void BaseDialog::paintEvent(QPaintEvent *event)
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    QRectF rect(10, 10, this->width() - 20, this->height()- 20);
    path.addRoundedRect(rect, 8, 8);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));
    QColor color(0, 0, 0, 50);
    for(int i=0; i<10; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        QRectF rect(10-i, 10-i, this->width()-(10-i)*2, this->height()-(10-i)*2);
        path.addRoundedRect(rect, 8, 8);
        color.setAlpha(150	- qSqrt(i)*50);
        painter.setPen(color);
        painter.drawPath(path);
    }
}
