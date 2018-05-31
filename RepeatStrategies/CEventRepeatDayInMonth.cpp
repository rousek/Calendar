//
// Created by matyas on 05/09/2018.
//

#include "CEventRepeatDayInMonth.h"

std::vector<CDate> CEventRepeatDayInMonth::TestRange(const CDate &date, const CDate &from, const CDate &to) const
{

}

int CEventRepeatDayInMonth::MonthLength(int month, int year)
{
    switch(month)
    {
        case 0: return 31;
        case 1:
            if (year % 4 || (!(year % 100) && year % 400))
                return 28;
            else
                return 29;
        case 2: return 31;
        case 3: return 30;
        case 4: return 31;
        case 5: return 30;
        case 6: return 31;
        case 7: return 31;
        case 8: return 30;
        case 9: return 31;
        case 10: return 30;
        case 11: return 31;
        default: throw std::invalid_argument("Wrong month: " + toStr(month));
    }
}

std::string CEventRepeatDayInMonth::ToStr() const
{
    return toStr("month_day ") + toStr(m_Day);
}