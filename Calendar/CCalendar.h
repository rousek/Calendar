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
    int m_EventCounter;
    std::map<int, CEvent *> m_Events;
    CSuggestor<CEvent *, CEvent::GetSearchable> m_Suggestions;

public:
    CCalendar();
    ~CCalendar();

    void AddEvent(CEvent * ev);
    void CreateEvent();
    std::map<int, CEvent *>::const_iterator FindEvent(int ID) const;
    void RemoveEvent(const std::map<int, CEvent *>::const_iterator & it);
    void RemoveEvent(int ID) { RemoveEvent(FindEvent(ID)); }
    void EditEvent(const std::map<int, CEvent *>::const_iterator & it);
    void EditEvent(int ID) { EditEvent(FindEvent(ID)); }
    void Clear();

    std::vector<CEvent *> SearchEvents(const std::string & name) const;
};


#endif //SEM_CCALENDAR_H
