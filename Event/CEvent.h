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
    int m_ID;
    std::string m_Title;
    std::string m_Place;
    std::string m_Summary;

    CDate m_Start;
    CDate m_End;
    int m_Priority;
    CEventRepeatBase * m_Repeat;

public:
    CEvent(int id, const std::string & title, const std::string & place, const std::string & summary,
               const CDate & start, const CDate & end, int priority, CEventRepeatBase * rp);

    ~CEvent();

    std::chrono::minutes GetDuration() const;

    void SetID(int id) { m_ID = id; }
    int GetID() const { return m_ID; }
    std::string GetTitle() const { return m_Title; }
    std::string GetPlace() const { return m_Place; }
    std::string GetSummary() const { return m_Summary; }
    std::string DurationString() const;

    bool InteractiveEditor();

    static CEvent * InteractiveCreator(int id);

    static CEventRepeatBase * ReadRepetition(std::istream & s);

    friend std::ostream & operator<<(std::ostream & s, const CEvent & ev);

    friend std::ostream & operator<<(std::ostream & s, const CEvent * ev);

    struct GetSearchable
    {
        std::vector<std::string> operator()(CEvent * const & ev) const;
    };
};



#endif //SEM_CEVENTBASE_H
