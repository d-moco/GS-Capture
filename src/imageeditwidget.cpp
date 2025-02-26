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
    //ui->vLayout->addWidget(m_imgViewTool);
    m_view = new ImageViewer();
    ui->vLayout->addWidget(m_view);
    connect(m_imgViewTool, &ImageViewToolWidget::sigImageOper, m_view, &ImageViewer::onImageOper);

    this->setStyleSheet("QPushButton { padding: 2px;}"
                        "QToolButton {"
                        "background-color: #404040; color: #00FFCC;"
                        "border: 2px;"
                        "border-radius: 8px;"
                        "padding: 6px;"
                        "font-size: 16px;"
                        "}"
                        "QToolButton:hover {"
                        "background-color: #444;"
                        "border: 2px solid #00CCFF;"
                        "}"
                        "QToolButton:pressed {"
                        "background-color: #222;"
                        "border: 2px solid #00BBEE;"
                        "}" );
}

ImageEditWidget::~ImageEditWidget()
{
    delete ui;
}
