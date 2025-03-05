#include "imageview.h"
#include "ui_imageview.h"
#include "toolbar.h"
#include "photoinfo.h"
#include <QPushButton>
#include <QWidget>
#include <QGridLayout>
#include <QFileInfo>
#include <QDragEnterEvent>
#include <QDesktopServices>
#include <QDropEvent>
#include <QMimeData>
#include <QDir>
#include <QLabel>
#include <QImage>
#include <QDebug>
#include <QMessageBox>
#include <QPainter>
#include <QFileDialog>
#include <QTranslator>


QStringList FileSuffix = (QStringList() << "png" <<
                          "jpg" << "jpeg" << "bmp" <<
                          "tif" << "tiff" << "webp" <<
                          "gif" << "jp2" << "dds" <<
                          "xpm" << "pnm" << "ppm" <<
                          "pgm" << "wbmp" << "ico" <<
                          "icns");

QStringList FileFilter = (QStringList() << "*.png" <<
                          "*.jpg" << "*.jpeg" << "*.bmp" <<
                          "*.tif" << "*.tiff" << "*.webp" <<
                          "*.gif" << "*.jp2" << "*.dds" <<
                          "*.xpm" << "*.pnm" << "*.ppm" <<
                          "*.pgm" << "*.wbmp" << "*.ico" <<
                          "*.icns");

ImageView::ImageView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageView)
{
    ui->setupUi(this);
    toolBar = new ToolBar();

    ui->statusBar->addPermanentWidget(toolBar,1);
    setCentralWidget(ui->photo);

    ui->statusBar->hide();

    PhotoIndex = 0;
    PhotoExist = false;
    ZoomFlag = false;
    ZoomFactor = 1.0;
    ZoomFactorFlag = true;
    windowMaxState = false;
}

ImageView::~ImageView()
{
    delete ui;

}

void ImageView::onImageOper(EImageOperation type)
{
    switch (type) {
    case eAddImg:
        Open();
        break;
    case eZoomInImg:
        ZoomIn();
        break;
    case eResetImg:
        ZoomFit();
        break;
    case eZoomOutImg:
        ZoomOut();
        break;
    case eDeleteImg:
        Delete();
        break;
    default:
        break;
    }
}

void ImageView::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
}

void ImageView::dropEvent(QDropEvent *event)
{
    foreach (const QUrl &purl, event->mimeData()->urls())
    {
        QFileInfo FileInfo(purl.toLocalFile());
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

            PhotoExist = true;
            ui->photo->setPixmap(FileInfo.absoluteFilePath());
            image.load(FileInfo.absoluteFilePath());
            image1.load(FileInfo.absoluteFilePath());
            PhotoIndex = 0;
            ui->statusBar->show();
            ZoomFit();
        }
    }
}


void ImageView::ZoomIn()
{
    if(PhotoExist)
    {
        if(!ZoomFlag)
        {
            Zoom();
            ZoomFlag = true;
        }
        ZoomFactor += 0.02;
        if(ZoomFactor >= 10.0)
            ZoomFactor = 10.0;
        QTransform tr = QTransform::fromScale(ZoomFactor,ZoomFactor);
        QImage image2 = image1.transformed(tr,Qt::SmoothTransformation);
        ui->photo->setPixmap(QPixmap::fromImage(image2));

        SetToolBarLabel();
    }
}


void ImageView::ZoomOut()
{
    if(PhotoExist)
    {
        if(!ZoomFlag)
        {
            Zoom();
            ZoomFlag = true;
        }
        ZoomFactor -= 0.02;
        if(ZoomFactor <= 0.01)
            ZoomFactor = 0.01;
        QTransform tr = QTransform::fromScale(ZoomFactor,ZoomFactor);
        QImage image2 = image1.transformed(tr,Qt::SmoothTransformation);
        ui->photo->setPixmap(QPixmap::fromImage(image2));

        SetToolBarLabel();
    }
}

void ImageView::ZoomFit()
{
    if(PhotoExist)
    {
        qreal pw = image1.width();
        qreal ph = image1.height();
        qreal ww = ui->photo->width();
        qreal wh = ui->photo->height();
        QImage image2;

        if(pw <= ww && ph <= wh)
        {
            image2 = image1;
        }
        else
        {
            image2 = image1.scaled(ui->photo->width(),ui->photo->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        }
        ui->photo->setPixmap(QPixmap::fromImage(image2));

        Zoom();
        SetToolBarLabel();
    }
}



void ImageView::resizeEvent (QResizeEvent *)
{
    if(PhotoExist == true)
    {
        ZoomFit();
    }
}

void ImageView::Info()
{
    if(PhotoExist)
    {
        PhotoInfo *photoInfo = new PhotoInfo(this);
        photoInfo->exec();
    }
}

void ImageView::Delete()
{
    if(PhotoExist)
    {
        QFileInfo FileInfo = PhotoMap[PhotoIndex];
        QFile file(FileInfo.absoluteFilePath());
        if(file.remove())
        {
            PhotoMap.remove(PhotoIndex);
            //PhotoIndex--;
        }
        else
        {
            QMessageBox msg(this);
            msg.setIcon(QMessageBox::Critical);
            msg.setWindowTitle(tr("Error"));
            msg.setText(tr("Can't Write File"));
            msg.setStandardButtons(QMessageBox::Ok);
            msg.setButtonText(QMessageBox::Ok, tr("OK"));
            msg.exec();
        }
    }
}

void ImageView::Open()
{
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
            PhotoExist = true;
            ui->photo->setPixmap(FileInfo.absoluteFilePath());
            image.load(FileInfo.absoluteFilePath());
            image1.load(FileInfo.absoluteFilePath());
            PhotoIndex = 0;
            ui->statusBar->show();
            ZoomFit();
        }
    }
}

QFileInfo ImageView::GetFileInfo()
{
    return PhotoMap.value(PhotoIndex);
}

QMap<int,QFileInfo> ImageView::GetAllFileInfo()
{
    return PhotoMap;
}

void ImageView::Zoom()
{
    qreal pw = image1.width();
    qreal ph = image1.height();
    qreal ww = ui->photo->width();
    qreal wh = ui->photo->height();

    qreal widthFactor = ww / pw;
    qreal heightFactor = wh / ph;

    ZoomFactorFlag = widthFactor <= heightFactor ? true : false;

    if(pw <= ww && ph <= wh)
    {
        ZoomFactor = 1.0;
    }
    else
    {
        if(ZoomFactorFlag)
        {
            ZoomFactor = widthFactor;
        }
        else
        {
            ZoomFactor = heightFactor;
        }
    }

}

void ImageView::SetToolBarLabel()
{
    QString str;
    int zoom = ZoomFactor * 100;
    str = tr("Zoom ") + QString::number(zoom) + "% | " + PhotoMap.value(PhotoIndex).fileName()
           + " | " + QString::number(image1.width()) + " x " + QString::number(image1.height());
    toolBar->label->setText(str);
}

void ImageView::closeEvent (QCloseEvent *event)
{

}
