#ifndef IMAGEVIEWTOOLWIDGET_H
#define IMAGEVIEWTOOLWIDGET_H

#include <QWidget>
#include <QToolButton>
#include "define.h"
#include "istylesheet.h"

class ImageViewToolWidget : public QWidget, public IStyleSheet
{
    Q_OBJECT
public:
    explicit ImageViewToolWidget(QWidget *parent = nullptr);

    virtual void refeshStyleSheet(EThemeColor clr = ComStyleSheet->getThemeClr());
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
