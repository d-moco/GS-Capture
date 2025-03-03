#include "imageviewer.h"

#include <QApplication>
#include <QClipboard>
#include <QColorSpace>
#include <QDir>
#include <QFileDialog>
#include <QImageReader>
#include <QImageWriter>
#include <QLabel>
#include <QMenuBar>
#include <QMessageBox>
#include <QMimeData>
#include <QPainter>
#include <QScreen>
#include <QScrollArea>
#include <QScrollBar>
#include <QStandardPaths>
#include <QStatusBar>
#include <QVBoxLayout>

#if defined(QT_PRINTSUPPORT_LIB)
#  include <QtPrintSupport/qtprintsupportglobal.h>

#  if QT_CONFIG(printdialog)
#    include <QPrintDialog>
#  endif
#endif

//! [0]
ImageViewer::ImageViewer(QWidget *parent)
   : QMainWindow(parent), photo(new QLabel)
{
    photo->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    QWidget* pwidget = new QWidget();
    QHBoxLayout* pLayout = new QHBoxLayout(pwidget);
    pLayout->addWidget(photo);
    setCentralWidget(pwidget);
    this->statusBar()->setSizeGripEnabled(false);

    ZoomFlag = false;
    ZoomFactor = 1.0;
    ZoomFactorFlag = true;
}

void ImageViewer::onImageOper(EImageOperation type)
{
     switch (type) {
     case eAddImg:
         open();
         break;
     case eZoomInImg:
         zoomIn();
         break;
     case eResetImg:
         normalSize();
         break;
     case eZoomOutImg:
         zoomOut();
         break;
     case eDeleteImg:
         break;
         break;
     default:
         break;
     }
}

bool ImageViewer::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }

    setImage(newImage);

    setWindowFilePath(fileName);

    const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
        .arg(QDir::toNativeSeparators(fileName)).arg(image.width()).arg(image.height()).arg(image.depth());
    statusBar()->showMessage(message);
    return true;
}

void ImageViewer::setImage(const QImage &newImage)
{
    image = newImage;
    QImage image2 = image.scaled(photo->width(), photo->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    photo->setPixmap(QPixmap::fromImage(image2));
}

static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    for (const QByteArray &mimeTypeName : supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");
    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("jpg");
}

void ImageViewer::open()
{
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
    //scrollArea->setWidgetResizable(true);
}

void ImageViewer::Zoom()
{
    qreal pw = image.width();
    qreal ph = image.height();
    qreal ww = photo->width();
    qreal wh = photo->height();

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


void ImageViewer::zoomIn()
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
    QImage image2 = image.transformed(tr,Qt::SmoothTransformation);
    if (image2.height() <= this->height() && image2.width() <= this->width()) {
        photo->setPixmap(QPixmap::fromImage(image2));
    } else {
        //ZoomFactor = 10.0;
    }
}

void ImageViewer::zoomOut()
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
    QImage image2 = image.transformed(tr,Qt::SmoothTransformation);

    if (image2.height() <= this->height() && image2.width() <= this->width()) {
        photo->setPixmap(QPixmap::fromImage(image2));
    } else {
        //ZoomFactor = 0.01;
    }
}

void ImageViewer::normalSize()
{
    qreal pw = image.width();
    qreal ph = image.height();
    qreal ww = photo->width();
    qreal wh = photo->height();
    QImage image2;

    if(pw <= ww && ph <= wh)
    {
        image2 = image;
    }
    else
    {
        image2 = image.scaled(photo->width(), photo->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    }

    photo->setPixmap(QPixmap::fromImage(image2));

    Zoom();
}
