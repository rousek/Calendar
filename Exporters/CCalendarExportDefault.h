//
// Created by matyas on 06/03/2018.
//

#ifndef SEM_CCALENDAREXPORTDEFAULT_H
#define SEM_CCALENDAREXPORTDEFAULT_H


#include "CCalendarExportBase.h"

class CCalendarExportDefault : public CCalendarExportBase
{
public:
    ~CCalendarExportDefault() override = default;
    void Import(std::ifstream & s, CCalendar & cal) const override;
    void Export(const CCalendar & cal, std::ofstream & s) const override;
private:
    void ThrowError(int line) const;

    static const std::string CALENDAR_START;
    static const std::string CALENDAR_END;
    static const std::string EVENT_START;
    static const std::string EVENT_END;
};

#endif //SEM_CCALENDAREXPORTDEFAULT_H
