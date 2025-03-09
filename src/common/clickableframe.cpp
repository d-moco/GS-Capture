#include "clickableframe.h"
#include "ui_clickableframe.h"
#include <QMouseEvent>
#include <qdebug.h>

ClickableFrame::ClickableFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ClickableFrame)
{
    ui->setupUi(this);

    setStyleSheet(
        "QFrame#frame:hover {"                // 鼠标悬停时生效
        "   background: #f0f0f0;"       // 悬停背景色
        "   border: 2px solid #0078d4;" // 悬停边框色
        "}"
        "QFrame#frame:hover QLabel {"
        "   color: black;"
        "}");
}

ClickableFrame::~ClickableFrame()
{
    delete ui;
}

void ClickableFrame::setImage(const QFileInfo& info)
{
    m_fileInfo = info;
    QPixmap originalPixmap;
    if(originalPixmap.load(m_fileInfo.absoluteFilePath())) {
        // 生成缩略图（保持宽高比，快速缩放）
        QPixmap thumbnail = originalPixmap.scaled(200, 200,
                                                  Qt::KeepAspectRatio,
                                                  Qt::FastTransformation);

        ui->label_image->setPixmap(thumbnail);
        ui->label_img_path->setText(m_fileInfo.fileName());
        ui->label_img_path->setToolTip(m_fileInfo.absoluteFilePath());
        m_strImgPath = m_fileInfo.absoluteFilePath();
    }
}

void ClickableFrame::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (m_strImgPath.size() > 0)
            emit doubleClicked(m_strImgPath); // 触发信号
        qDebug()<<"m_strImgPath:"<<m_strImgPath;
        event->accept();          // 标记事件已处理
    } else {
        QFrame::mouseDoubleClickEvent(event); // 其他按钮传递默认处理
    }
}
