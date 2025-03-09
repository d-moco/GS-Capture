#include "imageeditwidget.h"
#include "ui_imageeditwidget.h"
//#include "imageviewer.h"
#include "imageviewtoolwidget.h"
#include "imageview/imageview.h"
#include <QtCharts>

using namespace std;

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
    connect(m_view, &ImageView::sigSwitchImage, this, [=](const QString& strImg){
        ui->widget_2->loadImage(strImg);
    });

    initHistogram();
}

ImageEditWidget::~ImageEditWidget()
{
    delete ui;
}


void ImageEditWidget::switchImage(const QString& strPath)
{
    if (m_view) {
        m_view->switchImage(strPath);
    }
}

void ImageEditWidget::initHistogram()
{

}
