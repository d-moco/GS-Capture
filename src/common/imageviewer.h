#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include "define.h"
#include <QMainWindow>
#include <QImage>
#if defined(QT_PRINTSUPPORT_LIB)
#  include <QtPrintSupport/qtprintsupportglobal.h>

#  if QT_CONFIG(printer)
#    include <QPrinter>
#  endif
#endif

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;

QT_END_NAMESPACE

//! [0]
class ImageViewer : public QMainWindow
{
    Q_OBJECT

public:
    ImageViewer(QWidget *parent = nullptr);
    bool loadFile(const QString &);

public slots:
    void onImageOper(EImageOperation type);
private slots:
    void open();
    void zoomIn();
    void zoomOut();
    void normalSize();
private:
    void Zoom();
    void setImage(const QImage &newImage);
    QImage image;
    QLabel *photo;
    QScrollArea *scrollArea;
    double scaleFactor = 1;


    bool ZoomFlag;
    bool RotateFlipFlag;

    bool ZoomFactorFlag;
    qreal ZoomFactor;
};
//! [0]

#endif
