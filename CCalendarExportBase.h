//
// Created by matyas on 05/06/2018.
//

#ifndef SEM_CCALENDAREXPORTBASE_H
#define SEM_CCALENDAREXPORTBASE_H

#include "CCalendar.h"
#include <fstream>

class CCalendarExportBase {
public:
    virtual void Import(std::ifstream & s, CCalendar & cal);
    virtual void Export(const CCalendar & cal, std::ofstream & s);
};


#endif //SEM_CCALENDAREXPORTBASE_H
