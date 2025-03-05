#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H
#include "toolbar.h"
#include "photoinfo.h"
#include <QMainWindow>
#include <QPushButton>
#include <QFileInfo>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QImage>

#include "define.h"

namespace Ui {
class ImageView;
}

class ImageView : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageView(QWidget *parent = 0);
    ~ImageView();

    QFileInfo GetFileInfo();
    QMap<int,QFileInfo> GetAllFileInfo();
    void Zoom();
    void SetToolBarLabel();
public slots:
    void onImageOper(EImageOperation type);
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void resizeEvent (QResizeEvent *);
    void closeEvent (QCloseEvent *event);

private slots:
    void ZoomIn();
    void ZoomOut();
    void ZoomFit();
    void Info();
    void Delete();
    void Open();
private:
    Ui::ImageView *ui;
    ToolBar *toolBar;
    QImage image;
    QImage image1;
    QMap<int,QFileInfo> PhotoMap;
    bool windowMaxState;

    bool ZoomFlag;
    bool ZoomFactorFlag;
    qreal ZoomFactor;
    bool PhotoExist;
    int PhotoIndex;
};

#endif // IMAGEVIEW_H
