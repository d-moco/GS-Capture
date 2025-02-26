#include "countdownwidget.h"
#include "ui_countdownwidget.h"
#include <QPaintEvent>
#include <QPainter>

CountDownWidget::CountDownWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CountDownWidget)
{
    ui->setupUi(this);

    // 去除默认窗口边框并启用透明背景
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    ui->frame->setStyleSheet(
                    "QFrame#frame {"
                    "    background-color: #343434;"
                    "    border-radius: 10px;"
                    "    padding: 2px;"
                    "}"

                    /* 科技感的输入框样式 */
                    "QLineEdit {"
                    "    background-color: #343434;" /* 输入框背景颜色 */
                    "    color: #00FFCC;" /* 文本颜色 - 绿色荧光 */
                    "    border: 1px solid #0099FF;" /* 边框颜色 */
                    "    border-radius: 5px;" /* 圆角边框 */
                    "    padding: 5px;"
                    "    font-size: 14px;" /* 字体大小 */
                    "}"
        );
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

    // 使用你想要的颜色填充圆圈
    QBrush brush(QColor(0x404040)); // 替换为你想使用的颜色
    painter.setBrush(brush);

    // 设置画刷颜色并绘制圆形
    painter.setBrush(QColor("#404040")); // 圆形的颜色
    painter.drawEllipse(rect);
}
