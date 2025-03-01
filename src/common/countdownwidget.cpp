#include "countdownwidget.h"
#include "ui_countdownwidget.h"
#include <QPaintEvent>
#include <QPainter>
#include <QRegExpValidator>

CountDownWidget::CountDownWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CountDownWidget)
{
    ui->setupUi(this);

    // 去除默认窗口边框并启用透明背景
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    QRegExp regExp("[0-9]*");
    QRegExpValidator *validator = new QRegExpValidator(regExp, this);
    ui->edit_min->setValidator(validator);
    ui->edit_sec->setValidator(validator);
    ui->edit_msec->setValidator(validator);

    refeshStyleSheet();
}

void CountDownWidget::refeshStyleSheet(EThemeColor clr)
{
    m_themeClr = clr;
    if (clr == eDrak) {
        ui->frame->setStyleSheet(
            "QFrame#frame {"
                "    background-color: #31363B;" /* 调整为较浅的灰色 */
                "    border-radius: 10px;"
                "    padding: 2px;"
                "    border:none;"
                "}"

                /* 科技感的输入框样式 */
                "QLineEdit {"
                "    background-color: #505050;" /* 输入框背景颜色 - 更浅的灰色 */
                "    color: #66FF33;" /* 文本颜色 - 更亮的绿色荧光 */
                "    border: 1px solid #6699FF;" /* 边框颜色 - 更浅的蓝色 */
                "    border-radius: 5px;" /* 圆角边框 */
                "    padding: 5px;"
                "    font-size: 14px;" /* 字体大小 */
                "}");
    } else {
        ui->frame->setStyleSheet(
            "QFrame#frame {"
            "    background-color: #DDDDDD;" /* 调整为浅灰色，适应白色主题 */
            "    border-radius: 10px;"
            "    padding: 2px;"
            "    border:none;"
            "}"

            /* 科技感的输入框样式 */
            "QLineEdit {"
            "    background-color: #FFFFFF;" /* 输入框背景颜色 - 白色 */
            "    color: #000000;" /* 文本颜色 - 黑色，高对比度 */
            "    border: 1px solid #CCCCCC;" /* 边框颜色 - 浅灰色 */
            "    border-radius: 5px;" /* 圆角边框 */
            "    padding: 5px;"
            "    font-size: 14px;" /* 字体大小 */
            "}");
    }
}

CountDownWidget::~CountDownWidget()
{
    delete ui;
}

void CountDownWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿

    // 获取最小尺寸作为直径
    int diameter = qMin(width(), height());
    QRect rect((width() - diameter) / 2, (height() - diameter) / 2, diameter, diameter);

    // 设置无边框的画笔
    QPen pen(Qt::NoPen);
    painter.setPen(pen);

    // 设置画刷颜色并绘制圆形
    if (m_themeClr == eDrak)
        painter.setBrush(QColor("#333333")); // 圆形的颜色
    else
        painter.setBrush(QColor("#EEEEEE")); // 圆形的颜色
    painter.drawEllipse(rect);
}
