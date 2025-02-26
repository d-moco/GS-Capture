#ifndef CIRCULARBUTTON_H
#define CIRCULARBUTTON_H

#include <QPushButton>
#include <QPaintEvent>

class CircularButton : public QPushButton {
    Q_OBJECT

public:
    explicit CircularButton(QWidget *parent = nullptr);

    void setText(const QString &text); // 新增的接口方法

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override; // 重写鼠标按下事件

signals:
    void clicked(); // 已有的点击信号，这里主要是为了说明

private:
    QString buttonText; // 用于存储按钮文本
};

#endif // CIRCULARBUTTON_H
