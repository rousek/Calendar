#include <iostream>
#include <ctime>
#include "CDate.h"
#include "CEventBase.h"
#include "CCalendar.h"
#include "CCommandInterpreter.h"


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


int main() {
    CCalendar cal;

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

    CEventBase * ev = new CEventBase(
            "Narozeniny u me doma zmrdecci",
            "Doma",
            "Moje narozeniny",
            CDate(david),
            CDate(david2));

    CEventBase * ev2 = new CEventBase(
            "Narozeniny",
            "Doma",
            "Moje narozeniny",
            CDate(david),
            CDate(david2));

    //cout << ev << endl;

    //cout << CEventBase::InteractiveCreator() << endl;

    cal.AddEvent(ev);
    cal.AddEvent(ev2);

    auto found = cal.Search("narozeniny u");

    for (int i = 0; i < found.size(); i++)
        cout << found[i] << endl;

    return 0;
}