//
// Created by matyas on 05/09/2018.
//

#ifndef SEM_CEVENTREPEATDAYINMONTH_H
#define SEM_CEVENTREPEATDAYINMONTH_H

#include "CEventRepeatBase.h"
#include "../utils/utils.h"

/**
 * Allows expressions like 10. day in month.
 * Or last day of month.
 */
class CEventRepeatDayInMonth : public CEventRepeatBase
{
protected:
    std::set<CDate> TestRange(const CDate & date, const CDate::Interval & interval) const override;
public:
    /**
     * Constructor
     * @param day Non-zero number between -31 and 31.
     * Negative value means from the back.
     * E. g. -1 in January means 31. In February 28 and 29
     * for non-leap and leap respectively.
     * Throws invalid_argument if out of boundaries.
     * Event will not trigger if day is 30 and month is February.
     */
    explicit CEventRepeatDayInMonth(int day) : m_Day(day)
    {
        if (day > 31 || day == 0 || day < -31)
            throw std::invalid_argument(toStr("Invalid option of day: ") + toStr(day));
    }

    ~CEventRepeatDayInMonth() override = default;
    bool Delete(const CDate & date) override;
    CEventRepeatBase * Clone() const override { return new CEventRepeatDayInMonth(*this); }
    std::string ToStr() const override;
private:
    int m_Day;

    void Positive(const CDate &date, const CDate &to, std::set<CDate> &results, CDate current) const;
    void Negative(const CDate &date, const CDate &to, std::set<CDate> &results, CDate current) const;
};


#endif //SEM_CEVENTREPEATDAYINMONTH_H
