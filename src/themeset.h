#ifndef THEMESET_H
#define THEMESET_H

#include "QtCustomStylesheet.h"
#include <QDialog>

namespace Ui {
class ThemeSet;
}

class ThemeSet : public QDialog
{
    Q_OBJECT

public:
    explicit ThemeSet(qcss::QtCustomStylesheet* theme, QWidget *parent = nullptr);
    ~ThemeSet();

private:
    void initCtrl();
private:
    Ui::ThemeSet *ui;
    qcss::QtCustomStylesheet* m_currentTheme;
};

#endif // THEMESET_H
