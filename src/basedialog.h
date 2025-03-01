#ifndef BASEDIALOG_H
#define BASEDIALOG_H

#include <QDialog>
#include <QMap>
#include <QPaintEvent>
#include <QSignalMapper>
#include <QTimer>

#include "themeset.h"
#include "IStyleSheet.h"

namespace Ui {
    class BaseDialog;
}

class TitleBar;

class BaseDialog : public QDialog, public IStyleSheet
{
    Q_OBJECT

public:
    explicit BaseDialog(QWidget *parent = nullptr);
    ~BaseDialog();

    virtual void refeshStyleSheet(EThemeColor clr = ComStyleSheet->getThemeClr());
protected:
    void paintEvent(QPaintEvent *event);
private:
    void initTheme();
    void initWidget();
    void initToolButton();

signals:
    void sigChangeTheme(EThemeColor clr);
public slots:
    void onStyleManagerStylesheetChanged();

private:
    Ui::BaseDialog *ui;

    qcss::QtCustomStylesheet* m_customStyleSheet;
    TitleBar* m_titleBar;
    QSignalMapper* m_pToolBtnMapper;
};

#endif // BASEDIALOG_H
