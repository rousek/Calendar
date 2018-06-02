//
// Created by matyas on 05/02/2018.
//

#include "CDate.h"
#include "../utils/utils.h"
#include <iomanip>
#include <sstream>

const char CDate::TIME_FORMAT[] = "%H:%M";
const char CDate::DATE_FORMAT[] = "%d. %m. %Y";
const char CDate::SHORT_DATE_FORMAT[] = "%d. %m.";
const char CDate::WHOLE_FORMAT[] = "%d. %m. %Y %H:%M";

CDate::CDate()
{
    m_Date = {0};
    m_Date.tm_isdst = -1;
}

CDate::CDate(const std::string &str)
{
    m_Date = {0};

    std::stringstream ss(str);
    ss >> std::get_time(&m_Date, WHOLE_FORMAT);
    m_Date.tm_isdst = -1;

    if (mktime(&m_Date) == -1)
        throw std::invalid_argument("Invalid date string!");
}

CDate::CDate(const tm & tm)
{
    m_Date = tm;
    m_Date.tm_isdst = -1;

    if (mktime(&m_Date) == -1)
        throw std::invalid_argument("Invalid date 2!");
}

CDate::CDate(time_t number)
{
    if (number < 0)
        throw std::invalid_argument("Date must be at least 01. 01. 1970!");
    if (number > std::numeric_limits<time_t>::max())
        throw std::invalid_argument("Date is too big!");

    //number -= _timezone;
    m_Date.tm_isdst = -1;
    //m_Date = *gmtime(&number);
    m_Date = *localtime(&number);
}

time_t CDate::Count() const
{
    tm cpy = m_Date;
    return mktime(&cpy);
}

CDate& CDate::SetYear(int y)
{
    if (y >= 1970)
    {
        m_Date.tm_year = y - 1900;
        mktime(&m_Date);
        return *this;
    }
    else
    {
        throw std::invalid_argument("Year must be at least 1970!");
    }
}

CDate& CDate::SetMonth(int m)
{
    if (m > 0 && m < 13)
    {
        m_Date.tm_mon = m - 1;
        mktime(&m_Date);
        return *this;
    }
    else
    {
        throw std::invalid_argument("Month must be between 1 and 12!");
    }
}

CDate& CDate::SetDay(int d)
{
    if (d >= 1 && d <= MonthLength(GetMonth(), GetYear()))
    {
        m_Date.tm_mday = d;
        mktime(&m_Date);
        return *this;
    }
    else
    {
        throw std::invalid_argument("Invalid day!");
    }
}

CDate& CDate::SetHour(int h)
{
    if (h >= 0 && h < 24)
    {
        m_Date.tm_hour = h;
        mktime(&m_Date);
        return *this;
    }
    else
    {
        throw std::invalid_argument("Invalid hour!");
    }
}

CDate& CDate::SetMinute(int m)
{
    if (m >= 0 && m < 60)
    {
        m_Date.tm_min = m;
        mktime(&m_Date);
        return *this;
    }
    else
    {
        throw std::invalid_argument("Invalid minute!");
    }
}

bool CDate::operator == (const CDate & d2) const
{
    return Count() == d2.Count();
}

bool CDate::operator <= (const CDate & d2) const
{
    return Count() <= d2.Count();
}

bool CDate::operator < (const CDate & d2) const
{
    return Count() < d2.Count();
}

CDate CDate::operator+(const CDuration &duration) const
{
    tm cpy(m_Date);
    cpy.tm_mon = 0;
    cpy.tm_hour++; // UNIX timestamp starts at 01:00
    cpy.tm_year = 70;
    cpy.tm_isdst = -1;

    time_t timestamp = mktime(&cpy);
    if (timestamp == -1)
        throw std::invalid_argument("Invalid date 3!");

    CDuration dayAndTime = CDuration::Seconds(timestamp + duration.GetSeconds());
    CDuration::Separated separated(dayAndTime.Separate());

    tm cpyFinal(m_Date);
    cpyFinal.tm_year += duration.GetYears();
    cpyFinal.tm_mon += duration.GetMonths();
    // Days begin at index 1.
    cpyFinal.tm_mday = static_cast<int>(separated.weeks * CDuration::DAYS_IN_WEEK + separated.days + 1);
    // Hours don't but it didn't work any other way lol.
    cpyFinal.tm_hour = static_cast<int>(separated.hours);
    cpyFinal.tm_min = static_cast<int>(separated.minutes);
    cpyFinal.tm_sec = static_cast<int>(separated.seconds);

    return CDate(cpyFinal);
}

CDate& CDate::operator+=(const CDuration &duration)
{
    CDate newDate = operator+(duration);
    m_Date = newDate.m_Date;

    return *this;
}

CDate CDate::operator-(const CDuration &duration) const
{
    return operator+(-duration);
}

CDate& CDate::operator-=(const CDuration &duration)
{
    return operator+=(-duration);
}

CDuration CDate::operator-(const CDate &d2) const
{
    return CDuration::Seconds(Count() - d2.Count());
}

CDate CDate::ReadDate(std::istream & s)
{
    tm tm = {};
    std::string line;
    getline(s, line);
    std::stringstream ss(line);

    if (line.empty())
        throw EmptyLineException();

    ss >> std::get_time(&tm, DATE_FORMAT);

    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;

    if (ss.fail())
        throw std::invalid_argument("Invalid date! Date format: DD. MM. YYYY");

    return CDate(tm);
}

CDate CDate::ReadTime(std::istream & s)
{

    tm tm = {};
    std::string line;
    getline(s, line);
    std::stringstream ss(line);

    if (line.empty())
        throw EmptyLineException();

    ss >> std::get_time(&tm, TIME_FORMAT);

    tm.tm_sec = 0;
    tm.tm_mon = 0;
    tm.tm_mday = 1;
    tm.tm_year = 70; // 1970

    if (ss.fail())
        throw std::invalid_argument("Invalid time! Supported time format: HH:MM");

    return CDate(tm);
}

CDate CDate::RequestDateFromUser(std::function<CDate (std::istream &)> fn, bool required)
{
    CDate date;

    while(true)
    {
        try
        {
            date = fn(std::cin);
            break;
        }
        catch (const std::invalid_argument & e)
        {
            std::cout << e.what() << std::endl;
        }
        catch (const EmptyLineException & e)
        {
            if (required)
                std::cout << "This information is required!" << std::endl;
            else
                throw e;
        }
    }

    return date;
}

CDate CDate::CombineDateTime(const CDate & date, const CDate & time)
{
    tm tm = date.m_Date;
    tm.tm_hour = time.GetHour();
    tm.tm_min = time.GetMinute();

    return CDate(tm);
}

CDate CDate::StartOfMonth(int month, int year)
{
    tm tm = {0};
    tm.tm_isdst = -1;
    tm.tm_mday = 1;
    tm.tm_mon = month - 1;
    tm.tm_year = year - 1900;

    return CDate(tm);
}

CDate CDate::EndOfMonth(int month, int year)
{
    tm tm = {0};
    tm.tm_isdst = -1;
    tm.tm_mday = MonthLength(month, year);
    tm.tm_mon = month - 1;
    tm.tm_year = year - 1900;
    tm.tm_hour = 23;
    tm.tm_min = 59;
    tm.tm_sec = 59;

    return CDate(tm);
}

CDate CDate::Now()
{
    time_t t;
    time(&t);

    return CDate(t);
}


std::string CDate::DateToStr() const
{
    std::stringstream ss;
    ss << std::put_time(&m_Date, DATE_FORMAT);
    return ss.str();
}

std::string CDate::ShortDateToStr() const
{
    std::stringstream ss;
    ss << std::put_time(&m_Date, SHORT_DATE_FORMAT);
    return ss.str();
}


std::string CDate::TimeToStr() const
{
    std::stringstream ss;
    ss << std::put_time(&m_Date, TIME_FORMAT);
    return ss.str();
}

std::ostream & operator << (std::ostream & stream, const CDate & date)
{
    return stream << std::put_time(&date.m_Date, CDate::WHOLE_FORMAT);
}

std::ostream & operator << (std::ostream & stream, const CDate::Interval & interval)
{
    return stream << interval.first << " - " << interval.second;
}


int CDate::MonthLength(int month, int year)
{
    switch(month)
    {
        case 1: return 31;
        case 2:
            if (year % 4 || (!(year % 100) && year % 400))
                return 28;
            else
                return 29;
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
        default: throw std::invalid_argument("Wrong month: " + toStr(month));
    }
}

char const * CDate::MonthStringShort(int month)
{
    static const char MONTHS[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                       "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    return MONTHS[month - 1];
}

char const * CDate::MonthStringLong(int month)
{
    static const char MONTHS[12][10] = {"January", "February", "March", "April", "May",
                                        "June", "July", "August", "September", "October",
                                        "November", "December"};

    return MONTHS[month - 1];
}

char const * CDate::WeekdayStringShort(int weekday)
{
    static const char WEEKDAYS[12][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    return WEEKDAYS[weekday];
}

char const * CDate::WeekdayStringLong(int weekday)
{
    static const char WEEKDAYS[12][10] = {"Sunday", "Monday", "Tuesday", "Wednesday",
                                          "Thursday", "Friday", "Saturday"};

    return WEEKDAYS[weekday];
}