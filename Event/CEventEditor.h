//
// Created by matyas on 06/03/2018.
//

#ifndef SEM_CEVENTEDITOR_H
#define SEM_CEVENTEDITOR_H


#include "../Calendar/CCalendar.h"

class CEventEditor
{
public:
    static void Create(CCalendar & calendar);
    static void Edit(CCalendar & calendar, const CEvent::Instance & instance);
    static void Edit(CCalendar & calendar, CEvent * ev);
    static CEventRepeatBase * ParseRepeat(const std::string &str);
};


#endif //SEM_CEVENTEDITOR_H
