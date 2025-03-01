#ifndef SIGSLOTMGR_H
#define SIGSLOTMGR_H

#include <QMutex>
#include <QMutexLocker>
#include <QObject>
#include "commonstylesheet.h"

class SigSlotMgr : public QObject
{
    Q_OBJECT
public:
    explicit SigSlotMgr(QObject *parent = nullptr);

    // 禁止拷贝构造函数和赋值操作符
    SigSlotMgr(const SigSlotMgr&) = delete;
    SigSlotMgr& operator=(const SigSlotMgr&) = delete;

    static SigSlotMgr* inst();
signals:
    void sigChangeTheme(EThemeColor clr);
private:
    static SigSlotMgr* m_instance; // 静态成员变量，保存单例实例
};

#endif // SIGSLOTMGR_H
