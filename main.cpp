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


using namespace std;


class CViewBase
{
public:
    virtual void Draw() const;
    virtual void Previous();
    virtual void Next();

    void Help()
    {
    }
};

class CViewDay : public CViewBase
{

};


class CViewWeek : public CViewBase
{

};

class CViewMonth : public CViewBase
{

};

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
    assert(toStr(a.nextMonth()) == "05. 12. 2018 12:32");
    assert(toStr(a.nextMonth().nextMonth()) == "05. 01. 2019 12:32");

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


    assert(CDate::DurationToMinutes("1 hour, 1 hours") == CDate::DurationToMinutes("2 hours"));
    assert(CDate::DurationToMinutes("1500 minute, 1 hours").count() == 1560);
}


int main()
{
    CCalendar cal;

    DateTest();

    tm david = {0};
    david.tm_hour = 10;
    david.tm_min = 32;
    david.tm_mon = 1;
    david.tm_mday = 5;
    david.tm_year = 100;


    tm david2 = david;
    david2.tm_year = 101;
    david2.tm_min = 36;
    david2.tm_hour = 19;
    david2.tm_mday = 2;
    david2.tm_mon = 9;

    CEvent * ev = new CEvent(
            0,
            "Narozeniny u me doma",
            "Doma",
            "Moje narozeniny",
            CDate(david),
            CDate(david2),
            1,
            nullptr);

    CEvent * ev2 = new CEvent(
            1,
            "Narozeniny",
            "Doma",
            "Moje narozeniny",
            CDate(david),
            CDate(david2),
            1,
            nullptr);

    //cout << ev << endl;

    //cout << CEvent::InteractiveCreator() << endl;

    cal.AddEvent(ev);
    cal.AddEvent(ev2);

    auto found = cal.SearchEvents("narozeniny u");

    /*
    for (auto i : found)
        cout << i << endl;
        */

    CEventRepeatBase * repeat = new CEventRepeatAfter(std::chrono::minutes(3));

    CEventRepeatBase * repeat1 = new CEventRepeatDayInMonth(-5);

    cout << CDate(david) << endl;
    cout << CDate(david2) << endl << endl;
    for (auto a : repeat1->TestRange(CDate(david), CDate(david), CDate(david2)))
        cout << a << endl;


/*
    for (auto a : repeat->TestRange(CDate(david), CDate(david), CDate(david2)))
        cout << a << endl;
*/

    return 0;
}