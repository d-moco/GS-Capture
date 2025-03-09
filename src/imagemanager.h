#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QMap>
#include <QWidget>
#include <QFileInfo>

namespace Ui {
class ImageManager;
}

class ImageManager : public QWidget
{
    Q_OBJECT

public:
    explicit ImageManager(QWidget *parent = nullptr);
    ~ImageManager();

    void init();

signals:
    void sigOpenImageEdit(const QString& strImgPath);
private:
    Ui::ImageManager *ui;
    QMap<int,QFileInfo> PhotoMap;
};

#endif // IMAGEMANAGER_H
