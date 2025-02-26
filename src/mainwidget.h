#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "maintitlebar.h"

namespace Ui {
class MainWidget;
}


class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(EWindowType type, QWidget *parent = nullptr);
    ~MainWidget();

    void setWidgetType(EWindowType type);
private:
    void initStyleSheet();
private:
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
