#ifndef IMAGEEDITWIDGET_H
#define IMAGEEDITWIDGET_H

#include <QWidget>

namespace Ui {
class ImageEditWidget;
}

class ImageView;
class ImageViewToolWidget;

class ImageEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageEditWidget(QWidget *parent = nullptr);
    ~ImageEditWidget();

private:
    Ui::ImageEditWidget *ui;
    ImageView* m_view;
    ImageViewToolWidget* m_imgViewTool;
};

#endif // IMAGEEDITWIDGET_H
