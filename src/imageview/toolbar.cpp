#include "toolbar.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIcon>

ToolBar::ToolBar(QWidget *parent) : QWidget(parent)
{
    label = new QLabel;
    label->setObjectName("label");
    QHBoxLayout *labelLayout = new QHBoxLayout;
    labelLayout->addStretch();
    labelLayout->addWidget(label);
    labelLayout->addStretch();
    labelLayout->setContentsMargins(0,0,0,0);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addLayout(labelLayout);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(3);
    setWindowFlags(Qt::FramelessWindowHint);
}
