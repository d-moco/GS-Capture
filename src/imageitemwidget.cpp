#include "imageitemwidget.h"
#include "ui_imageitemwidget.h"
#include <QPixmap>

ImageItemWidget::ImageItemWidget(QVector<QFileInfo> fileInfo, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageItemWidget)
{
    ui->setupUi(this);
    m_imgInfo.swap(fileInfo);
    init();
}

ImageItemWidget::~ImageItemWidget()
{
    delete ui;
}

void ImageItemWidget::init()
{
    connect(ui->frame_1, &ClickableFrame::doubleClicked, this, &ImageItemWidget::doubleClicked);
    connect(ui->frame_2, &ClickableFrame::doubleClicked, this, &ImageItemWidget::doubleClicked);
    connect(ui->frame_3, &ClickableFrame::doubleClicked, this, &ImageItemWidget::doubleClicked);
//    m_imgMap[0] = ui->label_image_1;
//    m_imgMap[1] = ui->label_image_2;
//    m_imgMap[2] = ui->label_image_3;

//    m_imgPathMap[0] = ui->label_img_path_1;
//    m_imgPathMap[1] = ui->label_img_path_2;
//    m_imgPathMap[2] = ui->label_img_path_3;
    m_imgMap[0] = ui->frame_1;
    m_imgMap[1] = ui->frame_2;
    m_imgMap[2] = ui->frame_3;

    if (m_imgInfo.size() > 0) {

        int i = 0;
        for (auto m : m_imgInfo) {
            QFileInfo img = m_imgInfo.at(i);
            m_imgMap[i]->setImage(img);
//            QPixmap originalPixmap;
//            if(originalPixmap.load(img.absoluteFilePath())) {
//                // 生成缩略图（保持宽高比，快速缩放）
//                QPixmap thumbnail = originalPixmap.scaled(200, 200,
//                                                          Qt::KeepAspectRatio,
//                                                          Qt::FastTransformation);

//                m_imgMap[i]->setPixmap(thumbnail);
//                m_imgPathMap[i]->setText(img.fileName());
//                m_imgPathMap[i]->setToolTip(img.absoluteFilePath());
//            }
            i++;
        }
    }
}
