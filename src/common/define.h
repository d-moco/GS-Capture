#ifndef DEFINE_H
#define DEFINE_H

#include <QStringList>

enum EImageOperation {
    eNodefineImageOper,
    eAddImg,
    eZoomInImg,
    eResetImg,
    eZoomOutImg,
    eDeleteImg,
};

static QStringList FileSuffix = (QStringList() << "png" <<
                          "jpg" << "jpeg" << "bmp" <<
                          "tif" << "tiff" << "webp" <<
                          "gif" << "jp2" << "dds" <<
                          "xpm" << "pnm" << "ppm" <<
                          "pgm" << "wbmp" << "ico" <<
                          "icns");

static QStringList FileFilter = (QStringList() << "*.png" <<
                          "*.jpg" << "*.jpeg" << "*.bmp" <<
                          "*.tif" << "*.tiff" << "*.webp" <<
                          "*.gif" << "*.jp2" << "*.dds" <<
                          "*.xpm" << "*.pnm" << "*.ppm" <<
                          "*.pgm" << "*.wbmp" << "*.ico" <<
                          "*.icns");

#endif // DEFINE_H
