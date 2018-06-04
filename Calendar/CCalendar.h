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

    std::set<CEvent *> GetEvents() const { return m_Events; }
    void AddEvent(CEvent * ev);
    void DeleteEvent(CEvent * ev);
    void DeleteEvent(const CEvent::Instance & instance);
    std::vector<CEvent::Instance> FindInInterval(const CDate::Interval & interval) const;
    void Clear();
    std::vector<CEvent *> SearchEvents(const std::string & name) const;

    static const int WAKE_UP_HOUR;
    static const int SLEEPING_HOUR;
private:
    std::set<CEvent *> m_Events;
    CSuggestor<CEvent *, CEvent::GetSearchable> m_Suggestions;
};


#endif //SEM_CCALENDAR_H
