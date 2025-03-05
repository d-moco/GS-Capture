#ifndef TOOLBAR
#define TOOLBAR

#include <QToolBar>
#include <QWidget>
#include <QPushButton>
#include <QMenu>
#include <QLabel>
class ToolBar : public QWidget
{
    Q_OBJECT

public:
    ToolBar(QWidget *parent = 0);
    QLabel *label;
};


#endif // TOOLBAR

