//
// Created by matyas on 05/02/2018.
//

#ifndef SEM_CEVENTBASE_H
#define SEM_CEVENTBASE_H

#include <string>
#include <vector>
#include "../Date/CDate.h"
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
    class Instance
    {
    public:
        Instance(CEvent * ev, const CDate & start) :
                m_Event(ev),
                m_Time(std::make_pair(start, start + ev->GetDuration())),
                m_IsInstance(true) {}
        explicit Instance(CEvent * ev) : m_Event(ev), m_IsInstance(false) {}
        CEvent * GetEvent() const { return m_Event; }
        CDate::Interval GetTime() const { return m_Time; }
        bool IsInstance() const { return m_IsInstance; }
    private:
        CEvent * m_Event;
        CDate::Interval m_Time;
        bool m_IsInstance;
    };


    CEvent(const std::string & title, const std::string & place, const std::string & summary,
               const CDate & start, const CDate & end, int priority, CEventRepeatBase * rp);
    explicit CEvent(const CEvent * ev);

    ~CEvent();

    CDuration GetDuration() const;
    std::string GetTitle() const { return m_Title; }
    std::string GetPlace() const { return m_Place; }
    std::string GetSummary() const { return m_Summary; }
    std::string GetRepeat() const { return m_Repeat->ToStr(); }

    std::vector<Instance> FindInInterval(const CDate::Interval & interval) const;
    int InstancesLeft() const { return m_Repeat->InstancesLeft(); };
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
