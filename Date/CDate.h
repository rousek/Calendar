//
// Created by matyas on 05/02/2018.
//

#ifndef SEM_CDATE_H
#define SEM_CDATE_H


#include <ctime>
#include <iostream>
#include <functional>
#include <ratio>
#include <chrono>
#include "CDuration.h"

/**
 * Wrapper of tm struct defining useful methods like read/write format and arithmetics.
 */
class CDate
{
public:
    /**
     * Initialize date with zeroes as parameters.
     */
    CDate();

    /**
     * Initializes date from date string.
     * @param str Date string in format "dd. mm. yyyy hh:MM".
     */
    CDate(const std::string & str);

    /**
     * Initialize date with this tm struct.
     * @param tm Tm stuct to use.
     */
    explicit CDate(const tm & tm);

    /**
     * Initialize date with this time_t.
     * @param number
     */
    explicit CDate(time_t number);

    /**
     * @return Year of date. Integer.
     */
    int GetYear() const { return m_Date.tm_year + 1900; }

    /**
     * @return Month of date. Integer 1-12.
     */
    int GetMonth() const { return m_Date.tm_mon + 1; }

    /**
     * @return Day of date. Integer 1-31 (depending on month).
     */
    int GetDay() const { return m_Date.tm_mday; }
    /**
     * @return Hour of date. Integer 0-23.
     */
    int GetHour() const { return m_Date.tm_hour; }

    /**
     * @return Minute of date. Integer 0-59.
     */
    int GetMinute() const { return m_Date.tm_min; }

    /**
     * @return Return number of days since Sunday.
     */
    int GetWeekDay() const { return m_Date.tm_wday; }
    /**
     * @return time_t value. Useful for date arithmetics.
     */
    time_t Count() const;

    CDate & SetYear(int y);
    CDate & SetMonth(int m);
    CDate & SetDay(int d);
    CDate & SetHour(int h);
    CDate & SetMinute(int m);


    bool operator == (const CDate & d2) const;
    bool operator < (const CDate & d2) const;
    bool operator <= (const CDate & d2) const;

    bool operator != (const CDate & d2) const { return !operator==(d2); }
    bool operator > (const CDate & d2) const { return !operator<=(d2); }
    bool operator >= (const CDate & d2) const { return !operator<(d2); }

    CDate operator+(const CDuration & duration) const;
    CDate & operator+=(const CDuration & duration);
    CDate operator-(const CDuration & duration) const;
    CDate & operator-=(const CDuration & duration);

    CDuration operator-(const CDate & d2) const;

    /**
     * Return year, month and day in format set by CDate::DATE_FORMAT.
     * @return string
     */
    std::string DateToStr() const;

    /**
     * Return month and day in format set by CDate::DATE_FORMAT.
     * @return string
     */
    std::string ShortDateToStr() const;


    /**
     * Return hour and minute in format set by CDate::TIME_FORMAT.
     * @return string
     */
    std::string TimeToStr() const;


    /**
     * Reads year, month, day in format set by DATE_FORMAT.
     * Throws invalid_argument exception if format is incorrect.
     * @param s istream to be read.
     * @return CDate with set year, month and day.
     */
    static CDate ReadDate(std::istream & s);

    /**
     * Reads hour, minute in format set by TIME_FORMAT.
     * Throws invalid_argument exception if format is incorrect.
     * @param s istream to be read.
     * @return CDate with set hour and minute.
     */
    static CDate ReadTime(std::istream & s);

    /**
     *
     * @param fn Function which loads date from istream and validates it.
     * @param required If false, then throws EmptyLineException on empty line.
     * If true then requires date even after.
     * @return CDate
     */
    static CDate RequestDateFromUser(std::function<CDate (std::istream &)> fn, bool required);

    /**
     * @param date CDate providing year, month and day.
     * @param time CDate providing hour and minute.
     * @return Combined date and time.
     */
    static CDate CombineDateTime(const CDate & date, const CDate & time);

    /**
     * @param month
     * @param year
     * @return 01. XX. YYYY 00:00.
     */
    static CDate StartOfMonth(int month, int year);
    /**
     * @param month
     * @param year
     * @return (31|30|29|28). XX. YYYY 23:59.
     */
    static CDate EndOfMonth(int month, int year);
    /**
     * @return Current time read by function time.
     */
    static CDate Now();

    /**
     * @param month
     * @param year
     * @return Length of month in year.
     */
    static int MonthLength(int month, int year);

    /**
     * @param month Integer 1-12.
     * @return Three letters long char[].
     */
    static char const * MonthStringShort(int month);
    /**
     * @param month Integer 1-12.
     * @return Full sized name of month.
     */
    static char const * MonthStringLong(int month);
    /**
     * @param weekday Integer 0-6. 0 is for Sunday.
     * @return Three letters long char[].
     */
    static char const * WeekdayStringShort(int weekday);
    /**
     * @param weekday Integer 0-6. 0 is for Sunday.
     * @return Full sized name of weekday.
     */
    static char const * WeekdayStringLong(int weekday);


    typedef std::pair<CDate, CDate> Interval;

    friend std::ostream & operator << (std::ostream & stream, const CDate & date);

    friend std::ostream & operator << (std::ostream & stream, const CDate::Interval & interval);

private:
    tm m_Date;

    static const char TIME_FORMAT[];
    static const char DATE_FORMAT[];
    static const char SHORT_DATE_FORMAT[];
    static const char WHOLE_FORMAT[];
};

#endif //SEM_CDATE_H
