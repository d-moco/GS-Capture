#ifndef CLICKABLEFRAME_H
#define CLICKABLEFRAME_H

#include <QFrame>
#include <QFileInfo>

namespace Ui {
class ClickableFrame;
}

class ClickableFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ClickableFrame(QWidget *parent = nullptr);
    ~ClickableFrame();

    void setImage(const QFileInfo& info);
signals:
    void doubleClicked(const QString& strPath); // 传递自身指针

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
private:
    Ui::ClickableFrame *ui;
    QFileInfo m_fileInfo;
    QString m_strImgPath;
};

#endif // CLICKABLEFRAME_H
