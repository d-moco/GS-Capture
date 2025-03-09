#include "imagemanager.h"
#include "ui_imagemanager.h"
#include <QFileInfo>
#include <QFileDialog>
#include "define.h"
#include "imageitemwidget.h"

// 类型别名简化代码
using PhotoBatch = QVector<QFileInfo>;

ImageManager::ImageManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageManager)
{
    ui->setupUi(this);

    init();
}

ImageManager::~ImageManager()
{
    delete ui;
}

void ImageManager::init()
{
    connect(ui->btn_img_select, &QPushButton::pressed, [=](){
        QFileDialog OpenPhoto(this);
        OpenPhoto.setFileMode(QFileDialog::ExistingFile);
        OpenPhoto.setNameFilter("All Supported Files (*.png ; *.jpg ; *.jpeg ; *.bmp ; *.tif ; *.tiff ; *.webp ;"
                                "*.gif ; *.jp2 ; *.dds ; *.xpm ; *.pnm ; *.ppm ; *.pgm ; *.wbmp ; *.xbm ; *.pbm ;"
                                "*.ico ; *.icns);; All Files(*)");

        OpenPhoto.setWindowTitle(tr("Open Photo"));


        if(OpenPhoto.exec())
        {
            QStringList PhotoFile;
            PhotoFile = OpenPhoto.selectedFiles();

            QFileInfo FileInfo(PhotoFile.at(0));
            if(FileSuffix.contains(FileInfo.suffix(),Qt::CaseInsensitive))
            {
                PhotoMap.clear();
                PhotoMap[PhotoMap.count()] = FileInfo;
                QList<QFileInfo> fileInfoList = FileInfo.dir().entryInfoList(FileFilter);
                fileInfoList.removeOne(FileInfo);
                while(fileInfoList.count() > 0)
                {
                    PhotoMap[PhotoMap.count()] = fileInfoList.takeFirst();
                }
            }

            if (PhotoMap.size() > 0) {

                QList<PhotoBatch> allBatches;
                QMap<int, QFileInfo>::const_iterator it = PhotoMap.constBegin();

                // 分批提取核心逻辑
                while(it != PhotoMap.constEnd()) {
                    PhotoBatch currentBatch;

                    // 单次提取最多3个文件
                    for(int count = 0; count < 3 && it != PhotoMap.constEnd(); ++count) {
                        currentBatch.append(it.value());
                        ++it;
                    }

                    allBatches.append(currentBatch);
                }

                for(int i = 0; i < allBatches.size(); ++i) {
                    ImageItemWidget* widget = new ImageItemWidget(allBatches.at(i));
                    connect(widget, &ImageItemWidget::doubleClicked, this, &ImageManager::sigOpenImageEdit);
                    QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
                    //connect(widget, &InputCalibrationItemWidget::sigValueChanged, this, &CraneWidget::onValueChange);
                    item->setSizeHint(widget->sizeHint()); // 设置项的大小
                    ui->listWidget->setItemWidget(item, widget);
                }
            }
        }
    });
}
