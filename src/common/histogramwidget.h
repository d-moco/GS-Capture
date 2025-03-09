#ifndef HISTOGRAM_WIDGET_H
#define HISTOGRAM_WIDGET_H

#include <QWidget>
#include <QImage>
#include <QVector>

class HistogramWidget : public QWidget {
    Q_OBJECT
public:
    explicit HistogramWidget(QWidget *parent = nullptr);

    bool loadImage(const QString &fileName);
    void setImage(const QImage &image);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<int> m_histogram;
    QImage m_image;
    int m_maxCount;  // 直方图最大频数（用于Y轴刻度）

    QRect m_plotRect;  // 新增：坐标系的绘制区域（在绘制时计算）

    void calculateHistogram();
    void drawAxes(QPainter &painter);  // 绘制坐标轴
    void drawBars(QPainter &painter);   // 绘制柱状图
};

#endif
