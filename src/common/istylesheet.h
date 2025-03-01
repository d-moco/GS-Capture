#ifndef ISTYLESHEET_H
#define ISTYLESHEET_H

#include "commonstylesheet.h"

class IStyleSheet {
    virtual void refeshStyleSheet(EThemeColor clr = ComStyleSheet->getThemeClr()) = 0;
};

#endif // ISTYLESHEET_H
