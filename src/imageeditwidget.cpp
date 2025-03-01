#include "imageeditwidget.h"
#include "ui_imageeditwidget.h"
#include "imageviewer.h"
#include "imageviewtoolwidget.h"

ImageEditWidget::ImageEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageEditWidget)
{
    ui->setupUi(this);

    m_imgViewTool = new ImageViewToolWidget();
    ui->vLayout->addWidget(m_imgViewTool);
    m_view = new ImageViewer();
    ui->vLayout->addWidget(m_view);
    connect(m_imgViewTool, &ImageViewToolWidget::sigImageOper, m_view, &ImageViewer::onImageOper);
}

ImageEditWidget::~ImageEditWidget()
{
    delete ui;
}
