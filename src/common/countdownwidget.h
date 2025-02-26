#ifndef COUNTDOWNWIDGET_H
#define COUNTDOWNWIDGET_H

#include <QWidget>

namespace Ui {
class CountDownWidget;
}

class CountDownWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CountDownWidget(QWidget *parent = nullptr);
    ~CountDownWidget();
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    Ui::CountDownWidget *ui;
};

#endif // COUNTDOWNWIDGET_H
