// grayScaleSelector.cpp
#include "grayScaleSelector.h"
#include <QPainter>
#include <QMouseEvent>

GrayScaleSelector::GrayScaleSelector(QWidget *parent) : QWidget(parent), currentX(0), indicatorHeight(40) {
    setMinimumSize(256, 20); // 设置最小尺寸，不包括指示器高度
}

void GrayScaleSelector::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    // 绘制灰度颜色选择区域
    for(int x = 0; x < width(); ++x) {
        QColor color(qMin(x, 255), qMin(x, 255), qMin(x, 255)); // 创建灰色调色板
        painter.setPen(color);
        //painter.drawLine(x, 0, x, 20);
        painter.drawLine(x, 20, x, 40);
    }

    // 绘制指示器，确保它不会超出边界
    if (currentX >= 0 && currentX <= width()) {
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::red);
        int startX = qBound(0, currentX - 2, width() - 4); // 确保指示器完全可见
        painter.drawRect(startX, -indicatorHeight, 4, indicatorHeight*2);
    }
}

void GrayScaleSelector::mouseMoveEvent(QMouseEvent *event) {
    if(event->buttons() & Qt::LeftButton) {
        currentX = qBound(0, event->x(), width()); // 边界检查
        emit colorChanged(QColor(qMin(currentX, 255), qMin(currentX, 255), qMin(currentX, 255)));
        update(); // 重新绘制控件
    }
}

void GrayScaleSelector::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        currentX = qBound(0, event->x(), width()); // 边界检查
        emit colorChanged(QColor(qMin(currentX, 255), qMin(currentX, 255), qMin(currentX, 255)));
        update(); // 重新绘制控件
    }
}
