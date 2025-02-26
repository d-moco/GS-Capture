#ifndef IMAGEVIEWTOOLWIDGET_H
#define IMAGEVIEWTOOLWIDGET_H

#include <QWidget>
#include <QToolButton>
#include "define.h"

class ImageViewToolWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageViewToolWidget(QWidget *parent = nullptr);

private:
    void init();
signals:
    void sigImageOper(EImageOperation type);
private:
    QToolButton* m_pAdd;
    QToolButton* m_pZoomIn; //放大
    QToolButton* m_pReset;
    QToolButton* m_pZoomOut; //缩小
    QToolButton* m_pDeleteImage;
    //QToolButton* m_pZoomOut;
};

#endif // IMAGEVIEWTOOLWIDGET_H
