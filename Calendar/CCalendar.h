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
public:
    ~CCalendar();

    void CreateEvent();
    void AddEvent(CEvent * ev);
    void DeleteEvent(CEvent * ev);
    void DeleteEvent(const CEvent::Instance & instance);
    void EditEvent(CEvent * ev);
    void EditEvent(const CEvent::Instance & instance);
    std::vector<CEvent::Instance> FindInInterval(const CDate::Interval & interval) const;
    void Clear();
    std::vector<CEvent *> SearchEvents(const std::string & name) const;

private:
    std::set<CEvent *> m_Events;
    CSuggestor<CEvent *, CEvent::GetSearchable> m_Suggestions;

    std::vector<CEvent::Instance> CheckCollisions(const CDate::Interval & interval);
};


#endif //SEM_CCALENDAR_H
