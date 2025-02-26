// grayScaleSelector.h
#ifndef GRAYSCALESELECTOR_H
#define GRAYSCALESELECTOR_H

#include <QWidget>

class GrayScaleSelector : public QWidget {
    Q_OBJECT
public:
    explicit GrayScaleSelector(QWidget *parent = nullptr);

signals:
    void colorChanged(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    int currentX;
    int indicatorHeight;
};

#endif // GRAYSCALESELECTOR_H
