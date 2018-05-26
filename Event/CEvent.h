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

/**
 *
 */
class CEvent
{
protected:
    std::string m_Title;
    std::string m_Place;
    std::string m_Summary;

    CDate m_Start;
    CDate m_End;
    CEventTransferBase * m_Transfer;
    CEventRepeatBase * m_Repeat;

public:
    CEvent(const std::string & title, const std::string & place, const std::string & summary,
               const CDate & start, const CDate & end, CEventTransferBase * tr, CEventRepeatBase * rp);


    std::chrono::minutes GetDuration() const;

    const std::string & getTitle() const { return m_Title; }
    const std::string & getPlace() const { return m_Place; }
    const std::string & getSummary() const { return m_Summary; }

    std::ostream & PrintDuration(std::ostream & s) const;

    CEvent * InteractiveEditor();
    static CEvent * InteractiveCreator();

    friend std::ostream & operator<<(std::ostream & s, const CEvent & ev);

    friend std::ostream & operator<<(std::ostream & s, const CEvent * ev);

    struct GetSearchable
    {
        std::vector<std::string> operator()(CEvent * const & ev) const;
    };
};



#endif //SEM_CEVENTBASE_H
