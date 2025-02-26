#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "themeset.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    void initTheme();
    void initStyleSheet();
public slots:
    void onStyleManagerStylesheetChanged();
private:
    Ui::Widget *ui;

    qcss::QtCustomStylesheet* m_customStyleSheet;
};
#endif // WIDGET_H
