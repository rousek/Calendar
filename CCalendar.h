//
// Created by matyas on 05/03/2018.
//

#ifndef SEM_CCALENDAR_H
#define SEM_CCALENDAR_H

#include <vector>
#include <string>
#include "CSuggestor.h"
#include "CEventBase.h"

class CCalendar
{
private:
    std::vector<CEventBase *> m_Events;
    CSuggestor<CEventBase *, CEventBase::GetSearchable> m_Suggestions;

public:
    ~CCalendar();

    void AddEvent(CEventBase * ev);

    void RemoveEvent(CEventBase * ev);

    std::vector<CEventBase *> Search(const std::string & name) const;
};


#endif //SEM_CCALENDAR_H
