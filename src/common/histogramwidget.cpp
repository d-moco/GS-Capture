#include "histogramwidget.h"
#include <QPainter>
#include <QFontMetrics>
#include <QMessageBox>
#include <algorithm>
#include <QDebug>

HistogramWidget::HistogramWidget(QWidget *parent)
    : QWidget(parent), m_maxCount(0) {}


bool HistogramWidget::loadImage(const QString &fileName)
{
    QImage image(fileName);
    if (image.isNull()) {
        // 可以通过信号通知外部错误（推荐），或直接返回false
        return false;
    }
    setImage(image);
    return true;
}

// 直接设置 QImage 对象并计算直方图
void HistogramWidget::setImage(const QImage &image) {
    m_image = image.convertToFormat(QImage::Format_ARGB32);
    m_maxCount = 0;  // 重置最大值
    calculateHistogram();
    update(); // 触发重绘
}

// 计算灰度直方图
void HistogramWidget::calculateHistogram() {
    m_histogram.fill(0, 256); // 重置直方图
    m_maxCount = 0;
    if (m_image.isNull()) return;

    for (int y = 0; y < m_image.height(); ++y) {
        const QRgb *line = reinterpret_cast<const QRgb*>(m_image.constScanLine(y));
        for (int x = 0; x < m_image.width(); ++x) {
            int gray = qGray(line[x]);
            m_histogram[gray]++;

            // 动态更新最大值（避免二次遍历）
            if (m_histogram[gray] > m_maxCount) {
                m_maxCount = m_histogram[gray];
            }
        }
    }
}

// 核心改动：绘制函数分拆为坐标轴和柱状图
void HistogramWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);

    if (m_histogram.isEmpty() || m_maxCount == 0) {
        painter.drawText(rect(), Qt::AlignCenter, "No image loaded or invalid histogram");
        return;
    }

    if (m_histogram.isEmpty()) return;

    // --------------------------
    // 1. 绘制坐标轴
    // --------------------------
    drawAxes(painter);

    // --------------------------
    // 2. 绘制柱状图
    // --------------------------
    drawBars(painter);
}

// 绘制坐标轴和标签
void HistogramWidget::drawAxes(QPainter &painter) {
    painter.setRenderHint(QPainter::Antialiasing);

    // 定义边距（根据字体大小动态计算）
    QFontMetrics metrics(painter.font());
    int leftMargin = metrics.horizontalAdvance("10000") + 20;  // Y轴标签宽度
    int bottomMargin = metrics.height() + 10;                  // X轴标签高度
    int topMargin = 10;
    int rightMargin = 10;

    // 坐标系区域（实际绘图区）
    m_plotRect = QRect(
        leftMargin,
        topMargin,
        width() - leftMargin - rightMargin,
        height() - topMargin - bottomMargin
        );

    // --------------------------
    // 绘制Y轴
    // --------------------------
    painter.setPen(Qt::black);
    painter.drawLine(m_plotRect.bottomLeft(), m_plotRect.topLeft());

    // Y轴刻度（最多5个刻度）
    int numYTicks = 5;
    for (int i = 0; i < numYTicks; ++i) {  // 改为正向循环
        double ratio = static_cast<double>(i) / (numYTicks - 1); // 修正比例计算

        // 关键修正：从绘图区域底部开始计算
        int y = m_plotRect.bottom() - ratio * m_plotRect.height();

        // 计算对应的数值标签
        int value = qRound(ratio * m_maxCount);

        // 绘制刻度线（左侧短线）
        painter.drawLine(m_plotRect.left() - 5, y, m_plotRect.left(), y);

        // 绘制标签（右对齐）
        QString label = QString::number(value);
        int textWidth = metrics.horizontalAdvance(label);
        QRect labelRect(
            m_plotRect.left() - 10 - textWidth,  // X位置：刻度线左侧留空
            y - metrics.height() / 2,           // Y位置：垂直居中
            textWidth,                           // 文本宽度
            metrics.height()                     // 文本高度
            );
        painter.drawText(labelRect, Qt::AlignRight | Qt::AlignVCenter, label);
    }


    // --------------------------
    // 绘制X轴
    // --------------------------
    painter.drawLine(m_plotRect.bottomLeft(), m_plotRect.bottomRight());

    // X轴刻度（灰度值0-255，间隔50）
    int xStep = 50;
    for (int xValue = 0; xValue <= 255; xValue += xStep) {
        double ratio = static_cast<double>(xValue) / 255;
        int x = m_plotRect.left() + ratio * m_plotRect.width();

        // 绘制刻度线
        painter.drawLine(x, m_plotRect.bottom(), x, m_plotRect.bottom() + 5);

        // 绘制标签（居中）
        QString label = QString::number(xValue);
        QRect labelRect(x - metrics.horizontalAdvance(label) / 2,
                        m_plotRect.bottom() + 5,
                        metrics.horizontalAdvance(label),
                        metrics.height());
        painter.drawText(labelRect, Qt::AlignCenter, label);
    }
}

// 绘制柱状图（基于坐标轴边距调整）
void HistogramWidget::drawBars(QPainter &painter) {
    if (m_maxCount == 0) return;

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);

    int numBins = m_histogram.size();
    float barWidth = static_cast<float>(m_plotRect.width()) / numBins;

    for (int i = 0; i < numBins; ++i) {
        // 计算柱子的高度（根据Y轴范围）
        float barHeight = static_cast<float>(m_histogram[i]) / m_maxCount * m_plotRect.height();

        // 计算柱子位置（基于绘图区坐标系）
        float x = m_plotRect.left() + i * barWidth;
        float y = m_plotRect.bottom() - barHeight;

        painter.drawRect(QRectF(x, y, barWidth, barHeight));
    }
}
