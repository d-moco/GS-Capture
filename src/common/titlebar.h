#ifndef TITLE_BAR
#define TITLE_BAR

#include <QAction>
#include <QWidget>
#include <QToolButton>
#include <QHBoxLayout>
#include <QTranslator>

class QLabel;
class QPushButton;

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = 0);
    ~TitleBar();
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual bool eventFilter(QObject *obj, QEvent *event) override;

    void updateMaximize();
signals:
    void sigTheme();
private slots:
    void onClicked();
private:
    void InitMenuBtn(QHBoxLayout *m_pLayout);
    void InitFunctionBtn(QHBoxLayout *m_pLayout);
private:
    QHBoxLayout* m_pHBoxLayout;
    QLabel      *m_title;
    QPushButton *m_pMinButton;
    QPushButton *m_pCloseButton;
};

#endif // TITLE_BAR
