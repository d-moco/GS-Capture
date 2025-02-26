#ifndef MAINTITLEBAR_H
#define MAINTITLEBAR_H

#include <QWidget>
#include <QHBoxLayout>

class QLabel;
class QPushButton;
class QToolButton;

enum EWindowType {
    eNodefineWndType,
    eReturnWnd,
    eMainWnd,
    eSettingWnd,
    eImageMgrWnd,
    eImageEditWnd,
};

class MainTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit MainTitleBar(QWidget *parent = nullptr);

    void setReturnIsShow(const bool bShow);
private:
    void InitFunctionBtn(QHBoxLayout *m_pLayout);
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual bool eventFilter(QObject *obj, QEvent *event) override;
signals:
    void sigSwitchWnd(EWindowType type);
private slots:
    void onClicked();
private:
    QHBoxLayout* m_pHBoxLayout;
    QLabel      *m_title;
    QLabel      *m_temp;
    QToolButton *m_return;
    QToolButton *m_camera;
    QToolButton *m_imgMgr;
    QToolButton *m_setting;
    QToolButton *m_imgEdit;
    QPushButton *m_pWndBtn;
    QPushButton *m_pMinButton;
    QPushButton *m_pMaxButton;
    QPushButton *m_pCloseButton;
};

#endif // MAINTITLEBAR_H
