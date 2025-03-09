#ifndef IMAGEITEMWIDGET_H
#define IMAGEITEMWIDGET_H

#include <QMap>
#include <QWidget>
#include <QFileInfo>
#include <QVector>
#include <QLabel>

namespace Ui {
class ImageItemWidget;
}

class ClickableFrame;

class ImageItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageItemWidget(QVector<QFileInfo> fileInfo, QWidget *parent = nullptr);
    ~ImageItemWidget();

signals:
    void doubleClicked(const QString& strPath);
private:
    void init();
private:
    Ui::ImageItemWidget *ui;

    QVector<QFileInfo> m_imgInfo;
    QMap<int, ClickableFrame*> m_imgMap;
};

#endif // IMAGEITEMWIDGET_H
