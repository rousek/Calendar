//
// Created by matyas on 05/02/2018.
//

#ifndef SEM_CEVENTBASE_H
#define SEM_CEVENTBASE_H

#include <string>
#include <vector>
#include "../Date/CDate.h"
#include "../RepeatStrategies/CEventRepeatBase.h"

class CEventEditor;

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

        bool operator<(const Instance & i2) { return m_Time < i2.m_Time; }
        bool operator<=(const Instance & i2) { return m_Time <= i2.m_Time; }

        friend std::ostream & operator<<(std::ostream & stream, const CEvent::Instance & instance);
    private:
        CEvent * m_Event;
        CDate::Interval m_Time;
        bool m_IsInstance;
    };


    CEvent(const std::string & title, const std::string & place, const std::string & summary,
               const CDate & start, const CDate & end, int priority, CEventRepeatBase * rp);
    ~CEvent();

    CDuration GetDuration() const { return m_End - m_Start; };
    std::string GetTitle() const { return m_Title; }
    std::string GetPlace() const { return m_Place; }
    std::string GetSummary() const { return m_Summary; }
    CEventRepeatBase * GetRepeat() const { return m_Repeat; }
    CDate GetStart() const { return m_Start; }
    CDate GetEnd() const { return m_End; }
    int GetPriority() const { return m_Priority; }

    std::vector<Instance> FindInInterval(const CDate::Interval & interval) const;
    int InstancesLeft() const { return m_Repeat->InstancesLeft(); };
    bool DeleteInstance(const CDate & date);

    static const int MIN_PRIORITY;
    static const int MAX_PRIORITY;

    static CEvent * CopyInstance(const CEvent::Instance & instance);

    struct GetSearchable
    {
        std::vector<std::string> operator()(CEvent * const & ev) const;
    };

    friend std::ostream & operator<<(std::ostream & s, const CEvent & ev);
    friend std::ostream & operator<<(std::ostream & s, const CEvent * ev);
    friend CEventEditor;
};



#endif //SEM_CEVENTBASE_H
