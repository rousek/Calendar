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
    std::vector<CDate> TestRange(const CDate & date, const CDate & from, const CDate & to) const override;
    std::string ToStr() const override;
private:
    int m_Day;

    static int MonthLength(int month, int year);
};


#endif //SEM_CEVENTREPEATDAYINMONTH_H
