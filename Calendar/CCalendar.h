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
    std::vector<CEvent *> m_Events;
    CSuggestor<CEvent *, CEvent::GetSearchable> m_Suggestions;

public:
    ~CCalendar();

    void AddEvent(CEvent * ev);

    void RemoveEvent(CEvent * ev);

    std::vector<CEvent *> Search(const std::string & name) const;
};


#endif //SEM_CCALENDAR_H
