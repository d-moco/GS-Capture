#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QMap>
#include <QDialog>
#include "maintitlebar.h"

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = nullptr);
    ~MainDialog();

public slots:
    void onSwitchWindow(EWindowType type);
private:
    Ui::MainDialog *ui;
    MainTitleBar* m_titleBar;

    EWindowType m_currentType;
    QMap<EWindowType, QWidget*> m_wndMap;
};

#endif // MAINDIALOG_H
