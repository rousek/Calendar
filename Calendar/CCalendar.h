//
// Created by matyas on 05/03/2018.
//

#ifndef SEM_CCALENDAR_H
#define SEM_CCALENDAR_H

#include <vector>
#include <string>
#include "../utils/CSuggestor.h"
#include "../Event/CEvent.h"

class CCalendar
{
private:
    std::set<CEvent *> m_Events;
    CSuggestor<CEvent *, CEvent::GetSearchable> m_Suggestions;

public:
    ~CCalendar();

    void AddEvent(CEvent * ev);
    void CreateEvent();
    void DeleteEvent(CEvent * event);
    void DeleteEvent(CEvent * event, const CDate & date);
    void EditEvent(CEvent * event);
    std::map<CDate::Interval, CEvent *> FindInInterval(const CDate::Interval & interval) const;
    void Clear();
    std::vector<CEvent *> SearchEvents(const std::string & name) const;
};


#endif //SEM_CCALENDAR_H
