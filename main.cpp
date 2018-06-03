#include <iostream>
#include <ctime>
#include <cassert>
#include <sstream>
#include "Date/CDate.h"
#include "Event/CEvent.h"
#include "Calendar/CCalendar.h"
#include "UI/CCommandInterpreter.h"
#include "utils/utils.h"
#include "Event/CEventEditor.h"


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


    /*
    for (auto a : obed->FindInInterval(make_pair(CDate("01. 01. 2018 12:31"), CDate("02. 01. 2018 11:30"))))
        cout << a << endl;
        */


/*
    for (auto a : schuzka->FindInInterval(make_pair(CDate("01. 01. 2018 12:19"), CDate("01. 12. 2018 12:30"))))
        cout << a << endl;
*/
}


int main()
{
    /*
    CalendarTest();
    DateTest();
     */

    CCommandInterpreter in;

    CEvent * obed = new CEvent
            (
                    "Obed",
                    "domov skola restaurace kancelar",
                    "Normalni obed",
                    CDate("01. 01. 2018 11:30"),
                    CDate("01. 01. 2018 12:00"),
                    1,
                    CEventEditor::ParseRepeat("after 1 day")
            );

    CEvent * schuzka = new CEvent
            (
                    "Schuzka s klientem",
                    "kancelar",
                    "pravidelna schuzka",
                    CDate("01. 01. 2018 12:20"),
                    CDate("01. 01. 2018 15:20"),
                    9,
                    CEventEditor::ParseRepeat("month_day 31")
            );

    in.m_Calendar.AddEvent(obed);
    in.m_Calendar.AddEvent(schuzka);

    std::string evtName = "Random event TEsT ";
    std::string place = "in a galaxy far away";
    CDate evtStart = CDate("15. 05. 2018 10:00");

    for (int i = 0; i < 60; i++)
    {
        CEvent * test = new CEvent
                (
                        evtName + toStr(i),
                        place,
                        "",
                        evtStart,
                        evtStart + CDuration::Hours(2),
                        1,
                        CEventEditor::ParseRepeat("none")
        );

        evtStart += CDuration::Days(1);

        in.m_Calendar.AddEvent(test);
    }

    in.Run();

    return 0;
}