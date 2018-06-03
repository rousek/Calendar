//
// Created by matyas on 05/02/2018.
//

#ifndef SEM_CEVENTBASE_H
#define SEM_CEVENTBASE_H

#include <string>
#include <vector>
#include "../Date/CDate.h"
#include "../TransferStrategies/CEventTransferBase.h"
#include "../RepeatStrategies/CEventRepeatBase.h"

class CEvent
{
private:
    std::string m_Title;
    std::string m_Place;
    std::string m_Summary;

    CDate m_Start;
    CDate m_End;
    int m_Priority;
    CEventRepeatBase * m_Repeat;

public:
    CEvent(const std::string & title, const std::string & place, const std::string & summary,
               const CDate & start, const CDate & end, int priority, CEventRepeatBase * rp);

    ~CEvent();

    CDuration GetDuration() const;
    std::string GetTitle() const { return m_Title; }
    std::string GetPlace() const { return m_Place; }
    std::string GetSummary() const { return m_Summary; }
    std::string GetRepeat() const { return m_Repeat->ToStr(); }

    std::set<CDate::Interval> FindInInterval(const CDate::Interval & interval) const;
    bool DeleteInstance(const CDate & date);

    static const int MIN_PRIORITY;
    static const int MAX_PRIORITY;

    struct GetSearchable
    {
        std::vector<std::string> operator()(CEvent * const & ev) const;
    };

    friend std::ostream & operator<<(std::ostream & s, const CEvent & ev);
    friend std::ostream & operator<<(std::ostream & s, const CEvent * ev);
};



#endif //SEM_CEVENTBASE_H
