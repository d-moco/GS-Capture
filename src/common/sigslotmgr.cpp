#include "sigslotmgr.h"

SigSlotMgr* SigSlotMgr::m_instance = nullptr;

SigSlotMgr::SigSlotMgr(QObject *parent)
    : QObject{parent}
{

}

SigSlotMgr* SigSlotMgr::inst()
{
    static QMutex mutex;
    if (!m_instance)
    {
        QMutexLocker locker(&mutex);
        if (!m_instance)
        {
            m_instance = new SigSlotMgr();
        }
    }
    return m_instance;
}
