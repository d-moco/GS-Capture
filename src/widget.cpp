#include "widget.h"
#include "ui_widget.h"

//#include "customtitlebar.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint); // 创建无边框窗口

//    CustomTitleBar *titleBar = new CustomTitleBar();
//    connect(titleBar, &CustomTitleBar::sigTheme, [=](){
//        ThemeSet set(m_customStyleSheet);
//        set.exec();
//    });
//    ui->horizontalLayout->addWidget(titleBar);

//    titleBar->setStyleSheet("background-color: rgb(134,207,235);");

    initStyleSheet();
    initTheme();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initTheme()
{
    // win11下需要使用绝对路径
    //QString AppDir = qApp->applicationDirPath();
    //QString StylesDir = AppDir + "/styles";

//    QString StylesDir = STRINGIFY(STYLES_DIR);
//    m_customStyleSheet = new qcss::QtCustomStylesheet(this);
//    m_customStyleSheet->setStylesDirPath(StylesDir);
//    m_customStyleSheet->setCurrentStyle("qt_material");
//    m_customStyleSheet->setDefaultTheme();
//    m_customStyleSheet->updateStylesheet();
//    qApp->setStyleSheet(m_customStyleSheet->styleSheet());
//    connect(m_customStyleSheet, SIGNAL(stylesheetChanged()), this,
//            SLOT(onStyleManagerStylesheetChanged()));
}

void Widget::onStyleManagerStylesheetChanged()
{
    qApp->setStyleSheet(m_customStyleSheet->styleSheet());
}

void Widget::initStyleSheet()
{
    this->setStyleSheet(
        "QPushButton { padding: 2px;}"
            "QToolButton {"
                "   background-color: #2c3e50;" // 深色背景
                "   border: none;"
                "   border-radius: 10px;"
                "   padding: 10px;"
                "   margin: 4px;"
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
            "}");

//    ui->btn_hsjcx->setStyleSheet(
//        "QToolButton {"
//        "   background-color: #2c3e50;" // 深色背景
//        "   border: none;"
//        "   border-radius: 10px;"
//        "   padding: 10px;"
//        "   margin: 4px;"
//        "}"
//        "QToolButton:hover {"
//        "   background-color: #34495e;" // 稍微变亮一点的深色背景
//        "   border: 2px solid #3498db;" // 科技蓝边框
//        "}"
//        "QToolButton:pressed {"
//        "   background-color: #ecf0f1;" // 浅色背景，模拟按下效果
//        "   color: #2c3e50;" // 文字颜色变为深色
//        "   border: 2px solid #e74c3c;" // 警告红边框，增加对比度
//        "}"
//        "QToolButton:disabled {"
//        "   background-color: #bdc3c7;" // 灰色背景表示禁用状态
//        "   color: #ecf0f1;"
//        "}"
//        );

//    ui->btn_hxfgcx->setStyleSheet(
//        "QToolButton {"
//        "   background-color: #2c3e50;" // 深色背景
//        "   border: none;"
//        "   border-radius: 10px;"
//        "   padding: 10px;"
//        "   margin: 4px;"
//        "}"
//        "QToolButton:hover {"
//        "   background-color: #34495e;" // 稍微变亮一点的深色背景
//        "   border: 2px solid #3498db;" // 科技蓝边框
//        "}"
//        "QToolButton:pressed {"
//        "   background-color: #ecf0f1;" // 浅色背景，模拟按下效果
//        "   color: #2c3e50;" // 文字颜色变为深色
//        "   border: 2px solid #e74c3c;" // 警告红边框，增加对比度
//        "}"
//        "QToolButton:disabled {"
//        "   background-color: #bdc3c7;" // 灰色背景表示禁用状态
//        "   color: #ecf0f1;"
//        "}"
//        );

//    ui->btn_dbjcx->setStyleSheet(
//        "QToolButton {"
//        "   background-color: #2c3e50;" // 深色背景
//        "   border: none;"
//        "   border-radius: 10px;"
//        "   padding: 10px;"
//        "   margin: 4px;"
//        "}"
//        "QToolButton:hover {"
//        "   background-color: #34495e;" // 稍微变亮一点的深色背景
//        "   border: 2px solid #3498db;" // 科技蓝边框
//        "}"
//        "QToolButton:pressed {"
//        "   background-color: #ecf0f1;" // 浅色背景，模拟按下效果
//        "   color: #2c3e50;" // 文字颜色变为深色
//        "   border: 2px solid #e74c3c;" // 警告红边框，增加对比度
//        "}"
//        "QToolButton:disabled {"
//        "   background-color: #bdc3c7;" // 灰色背景表示禁用状态
//        "   color: #ecf0f1;"
//        "}"
//        );


//    ui->btn_dsygcx->setStyleSheet(
//        "QToolButton {"
//        "   background-color: #2c3e50;" // 深色背景
//        "   border: none;"
//        "   border-radius: 10px;"
//        "   padding: 10px;"
//        "   margin: 4px;"
//        "}"
//        "QToolButton:hover {"
//        "   background-color: #34495e;" // 稍微变亮一点的深色背景
//        "   border: 2px solid #3498db;" // 科技蓝边框
//        "}"
//        "QToolButton:pressed {"
//        "   background-color: #ecf0f1;" // 浅色背景，模拟按下效果
//        "   color: #2c3e50;" // 文字颜色变为深色
//        "   border: 2px solid #e74c3c;" // 警告红边框，增加对比度
//        "}"
//        "QToolButton:disabled {"
//        "   background-color: #bdc3c7;" // 灰色背景表示禁用状态
//        "   color: #ecf0f1;"
//        "}"
//        );
}

