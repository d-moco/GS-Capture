#ifndef COMMONSTYLESHEET_H
#define COMMONSTYLESHEET_H

#include <QMutex>
#include <QMutexLocker>
#include <QObject>

enum EThemeColor {
    eNofineTheme,
    eDrak,
    eLight,
};

#define DRAK_TITLE_BAR_FONT_COLOR QString("#1296db")
#define LIGHT_TITLE_BAR_FONT_COLOR QString("#808080")

class CommonStyleSheet : public QObject
{
    Q_OBJECT
public:
    explicit CommonStyleSheet(QObject *parent = nullptr);

    // 禁止拷贝构造函数和赋值操作符
    CommonStyleSheet(const CommonStyleSheet&) = delete;
    CommonStyleSheet& operator=(const CommonStyleSheet&) = delete;

    static CommonStyleSheet* inst();

    void setThemeClr(const EThemeColor& clr);
    EThemeColor getThemeClr()const;
signals:
    void sigChangeTheme(EThemeColor clr);
private:
    static CommonStyleSheet* m_instance; // 静态成员变量，保存单例实例

    EThemeColor m_themeClr;
};

#define ComStyleSheet (CommonStyleSheet::inst())

#endif // COMMONSTYLESHEET_H
