#include "CircularButton.h"
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>

CircularButton::CircularButton(QWidget *parent)
    : QPushButton(parent), buttonText("") // 初始化buttonText为空字符串
{
    setFixedSize(100, 100); // 设置固定大小以确保它是圆形
}

void CircularButton::setText(const QString &text) {
    buttonText = text;
    update(); // 更新控件以触发重绘事件
}

void CircularButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿

    if (this->isDown()) {
        painter.setBrush(QColor("#848484")); // 按下时的颜色
    } else {
        painter.setBrush(QColor("#64B5F6")); // 正常状态下的颜色
    }
    painter.setPen(Qt::NoPen); // 无边框

    int diameter = qMin(width(), height());
    QRect rect((width() - diameter) / 2, (height() - diameter) / 2, diameter, diameter);

    painter.drawEllipse(rect); // 绘制圆形背景

    painter.setPen(QColor("#000000")); // 文字颜色为白色
    QFont font = painter.font();
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(rect, Qt::AlignCenter, buttonText); // 使用buttonText绘制文本
}

void CircularButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked(); // 发出点击信号
    }
    QPushButton::mousePressEvent(event); // 调用基类的鼠标按下事件处理器
}
