#ifndef COUNTDOWNWIDGET_H
#define COUNTDOWNWIDGET_H

#include <QWidget>
#include "istylesheet.h"

namespace Ui {
class CountDownWidget;
}

class CountDownWidget : public QWidget, public IStyleSheet
{
    Q_OBJECT

public:
    explicit CountDownWidget(QWidget *parent = nullptr);
    ~CountDownWidget();
    void refeshStyleSheet(EThemeColor clr = ComStyleSheet->getThemeClr());
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    Ui::CountDownWidget *ui;
    EThemeColor m_themeClr;
};

#endif // COUNTDOWNWIDGET_H
