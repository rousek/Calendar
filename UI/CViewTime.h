//
// Created by matyas on 06/02/2018.
//

#include "../Event/CEvent.h"
#include "../Calendar/CCalendar.h"
#include "CViewBase.h"

#ifndef SEM_CVIEWTIME_H
#define SEM_CVIEWTIME_H


/**
 * Common parent of CViewDay, Week, Month and year.
 */
class CViewTime : public CViewBase<CEvent::Instance>
{
public:
    /**
     * @param calendar Reference to calendar.
     * @param date Reference to date of CCommandInterpreter.
     */
    CViewTime(const CCalendar & calendar, CDate & date) : m_Calendar(calendar), m_Date(date) {}
protected:
    const CCalendar & m_Calendar;
    CDate & m_Date;
    std::map<int, CEvent::Instance> m_List;
};

#endif //SEM_CVIEWTIME_H
