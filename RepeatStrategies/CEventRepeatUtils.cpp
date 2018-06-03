//
// Created by matyas on 06/02/2018.
//

#include "CEventRepeatUtils.h"
#include "CEventRepeatDisabled.h"
#include "CEventRepeatDayInMonth.h"
#include "CEventRepeatAfter.h"
#include "../utils/utils.h"

CEventRepeatBase * RepetitionFromStr(const std::string & str)
{
    auto parts = split(str, ' ');

    try
    {
        if (parts.empty())
            throw 0;

        if (parts.size() == 1)
        {
            if (parts[0] == "none")
                return new CEventRepeatDisabled();

            throw 0;
        }
        else if (parts.size() == 2)
        {
            if (parts[0] == "month_day")
            {
                int day = parseInt(parts[1]);
                return new CEventRepeatDayInMonth(day);
            }

            throw 0;
        }
        else
        {
            if (parts[0] == "after")
            {
                const int offset = 6; // Offset in str after string "after "
                CDuration duration = CDuration(str.substr(offset));
                return new CEventRepeatAfter(duration);
            }

            throw 0;
        }
    }
    catch (...)
    {
        const char help[] =
                "Invalid input!\n"
                        "Valid options are:\n"
                        "\"none\"\n"
                        "\"month_day day\" where day is day of month. Negative values are also accepted.\n"
                        "\"after duration\" where duration is string representation of duration i.e. \"1 day, 1 month, 2 hours\"\n";

        throw std::invalid_argument(help);
    }
}
