//
// Created by matyas on 05/06/2018.
//

#ifndef SEM_CCALENDAREXPORTBASE_H
#define SEM_CCALENDAREXPORTBASE_H

#include "../Calendar/CCalendar.h"
#include <fstream>

/**
 * Basic interface for import/export.
 */
class CCalendarExportBase {
public:
    virtual ~CCalendarExportBase() = default;
    virtual void Import(std::ifstream & s, CCalendar & cal) const = 0;
    virtual void Export(const CCalendar & cal, std::ofstream & s) const = 0;
};

#endif //SEM_CCALENDAREXPORTBASE_H
