#include <iostream>
#include <ctime>
#include <cassert>
#include <sstream>
#include "Date/CDate.h"
#include "Event/CEvent.h"
#include "Calendar/CCalendar.h"
#include "UI/CCommandInterpreter.h"
#include "utils/utils.h"


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

}


int main()
{
    CCalendar cal;

    DateTest();

    return 0;

    tm david = {0};
    david.tm_hour = 12;
    david.tm_min = 32;
    david.tm_mon = 10;
    david.tm_mday = 5;
    david.tm_year = 118;

    tm david2 = david;
    david2.tm_min = 36;
    david2.tm_hour = 9;
    david2.tm_mday = 1;
    david2.tm_mon = 11;

    CEvent * ev = new CEvent(
            "Narozeniny u me doma",
            "Doma",
            "Moje narozeniny",
            CDate(david),
            CDate(david2),
            NULL,
            NULL);

    CEvent * ev2 = new CEvent(
            "Narozeniny",
            "Doma",
            "Moje narozeniny",
            CDate(david),
            CDate(david2),
            NULL,
            NULL);

    //cout << ev << endl;

    cout << CEvent::InteractiveCreator() << endl;

    cal.AddEvent(ev);
    cal.AddEvent(ev2);

    auto found = cal.Search("narozeniny u");

    for (int i = 0; i < found.size(); i++)
        cout << found[i] << endl;

    return 0;
}