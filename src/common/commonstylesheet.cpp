#include "commonstylesheet.h"
#include "qmutex.h"

CommonStyleSheet* CommonStyleSheet::m_instance = nullptr;

CommonStyleSheet::CommonStyleSheet(QObject *parent)
    : QObject{parent}, m_themeClr(eDrak)
{

}

CommonStyleSheet* CommonStyleSheet::inst()
{
    static QMutex mutex;
    if (!m_instance)
    {
        QMutexLocker locker(&mutex);
        if (!m_instance)
        {
            m_instance = new CommonStyleSheet();
        }
    }
    return m_instance;
}

void CommonStyleSheet::setThemeClr(const EThemeColor& clr)
{
    m_themeClr = clr;
}

EThemeColor CommonStyleSheet::getThemeClr()const
{
    return m_themeClr;
}
