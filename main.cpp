#include <iostream>
#include <ctime>
#include <cassert>
#include <sstream>
#include "Date/CDate.h"
#include "Event/CEvent.h"
#include "Calendar/CCalendar.h"
#include "UI/CCommandInterpreter.h"
#include "utils/utils.h"
#include "RepeatStrategies/CEventRepeatAfter.h"
#include "RepeatStrategies/CEventRepeatDayInMonth.h"
#include "UI/CViewYear.h"
#include "UI/CViewMonth.h"
#include "UI/CViewWeek.h"


using namespace std;


void DateTest()
{
    tm t = {0};
    t.tm_hour = 12;
    t.tm_min = 32;
    t.tm_mon = 10;
    t.tm_mday = 5;
    t.tm_year = 118;

    CDate a(t);

    assert(toStr(a) == "05. 11. 2018 12:32");

    stringstream timeS("12:32\n"),
                 dateS("05. 11. 2018\n");

    CDate time = CDate::ReadTime(timeS),
          date = CDate::ReadDate(dateS);

    CDate b = CDate::CombineDateTime(date, time);

    assert(a == b);

    timeS.seekg(0);
    dateS.seekg(0);

    assert(time == CDate::ReadTime(timeS));
    assert(date == CDate::ReadDate(dateS));


    assert(CDuration("1 hour, 1 hours") == CDuration("2 hours"));
    assert(CDuration("1500 minute, 1 hours").GetSeconds() == CDuration::Minutes(1560).GetSeconds());
}

void CalendarTest()
{
    CCalendar cal;
    stringstream ss("after 1 day");

    CEvent * obed = new CEvent
            (
                    0,
                    "Obed",
                    "domov skola restaurace kancelar",
                    "Normalni obed",
                    CDate("01. 01. 2018 11:30"),
                    CDate("01. 01. 2018 12:00"),
                    1,
                    CEvent::ReadRepetition(ss)
            );

    /*
    for (auto a : obed->FindInInterval(make_pair(CDate("01. 01. 2018 12:31"), CDate("02. 01. 2018 11:30"))))
        cout << a << endl;
        */

    ss = stringstream("month_day 31"); // last day in month

    CEvent * schuzka = new CEvent
            (
                    1,
                    "Schuzka s klientem",
                    "kancelar",
                    "pravidelna schuzka",
                    CDate("01. 01. 2018 12:20"),
                    CDate("01. 01. 2018 15:20"),
                    9,
                    CEvent::ReadRepetition(ss)
            );
/*
    for (auto a : schuzka->FindInInterval(make_pair(CDate("01. 01. 2018 12:19"), CDate("01. 12. 2018 12:30"))))
        cout << a << endl;
*/
    cal.AddEvent(obed);
    cal.AddEvent(schuzka);

    CDate date = CDate("01. 01. 2018 12:20");

    CViewWeek(cal, date).Update();
}


int main()
{
    CalendarTest();
    DateTest();

    return 0;
}