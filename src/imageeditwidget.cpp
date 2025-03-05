#include "imageeditwidget.h"
#include "ui_imageeditwidget.h"
//#include "imageviewer.h"
#include "imageviewtoolwidget.h"
#include "imageview/imageview.h"

ImageEditWidget::ImageEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageEditWidget)
{
    ui->setupUi(this);

    m_imgViewTool = new ImageViewToolWidget();
    ui->vLayout->addWidget(m_imgViewTool);
    m_view = new ImageView();
    ui->vLayout->addWidget(m_view);
    ui->vLayout->setStretch(0,0);
    ui->vLayout->setStretch(1,1);
    connect(m_imgViewTool, &ImageViewToolWidget::sigImageOper, m_view, &ImageView::onImageOper);
}

ImageEditWidget::~ImageEditWidget()
{
    delete ui;
}
