//
// Created by matyas on 05/02/2018.
//

#ifndef SEM_CEVENTBASE_H
#define SEM_CEVENTBASE_H

#include <string>
#include <vector>
#include "CDate.h"


class CEventBase
{
protected:
    std::string m_Title;
    std::string m_Place;
    std::string m_Summary;
    std::vector<std::string> m_People;

    CDate m_Start;
    CDate m_End;

public:
    CEventBase(const std::string & title, const std::string & place, const std::string & summary,
               const CDate & start, const CDate & end);


    std::chrono::minutes GetDuration() const;

    const std::string & getTitle() const { return m_Title; }
    const std::string & getPlace() const { return m_Place; }
    const std::string & getSummary() const { return m_Summary; }

    void PrintDuration(std::ostream & s) const;

    virtual bool TestDay(const CDate & date) const;

    virtual std::vector<CDate> TestRange(const CDate & from, const CDate & to) const;

    static CEventBase * InteractiveCreator();

    friend std::ostream & operator<<(std::ostream & s, const CEventBase & ev);

    friend std::ostream & operator<<(std::ostream & s, const CEventBase * ev);

    struct GetSearchable
    {
        std::vector<std::string> operator()(CEventBase * const & ev) const;
    };
};



#endif //SEM_CEVENTBASE_H
