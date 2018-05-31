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

/**
 * Wrapper of tm struct defining useful methods like read/write format
 * and arithmetics. This implementation ignores seconds.
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
     * @param tm tm stuct to use
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
    int GetYear() const;

    /**
     * @return Month of date. Integer 1-12.
     */
    int GetMonth() const;

    /**
     * @return Day of date. Integer 1-31 (depending on month).
     */
    int GetDay() const;
    /**
     * @return Hour of date. Integer 0-23.
     */
    int GetHour() const;

    /**
     * @return Minute of date. Integer 0-59.
     */
    int GetMinute() const;

    /**
     * @return time_t value. Useful for date arithmetics.
     */
    time_t Count() const;

    /**
     * @return copy of underlying tm struct.
     */
    tm GetTm()  const;

    bool operator == (const CDate & d2) const;
    bool operator < (const CDate & d2) const;
    bool operator <= (const CDate & d2) const;

    bool operator != (const CDate & d2) const { return !operator==(d2); }
    bool operator > (const CDate & d2) const { return !operator<=(d2); }
    bool operator >= (const CDate & d2) const { return !operator<(d2); }

    /**
     * Reads year, month, day in format set by DATE_FORMAT.
     * Throws invalid_argument exception if format is incorrect.
     * @param s istream to be read
     * @return CDate with set year, month and day
     */
    static CDate ReadDate(std::istream & s);

    /**
     * Reads hour, minute in format set by TIME_FORMAT.
     * Throws invalid_argument exception if format is incorrect.
     * @param s istream to be read
     * @return CDate with set hour and minute
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
     * @param date CDate providing year, month and day
     * @param time CDate providing hour and minute
     * @return Combined date and time
     */
    static CDate CombineDateTime(const CDate & date, const CDate & time);

    /**
     * Converts duration in minutes into human readable format.
     * @param minutesCount Number of minutes.
     * @return string like this: "X days, Y hours, Z minutes"
     */
    static std::string GetFormattedDuration(long long int minutesCount);

    /**
     * Converts duration string to std::chrono::minutes.
     * @param duration String like this: "1 days, 4 hours, 2 minutes, 3 days". Does not support seconds.
     * @return duration in minutes.
     */
    static std::chrono::minutes DurationToMinutes(std::string duration);

    /**
     * @param month
     * @param year
     * @return Length of month in year.
     */
    static int MonthLength(int month, int year);

    /**
     * Print year, month and day in format set by CDate::DATE_FORMAT
     * @param stream
     * @return ostream &
     */
    std::ostream & PrintDate(std::ostream & stream) const;

    /**
     * Print hour and minute in format set by CDate::TIME_FORMAT
     * @param stream
     * @return ostream &
     */
    std::ostream & PrintTime(std::ostream & stream) const;


    friend std::ostream & operator << (std::ostream & stream, const CDate & date);

    /**
     * C++11 polyfill of chrono::days
     */
    typedef std::chrono::duration<int64_t, std::ratio<86400>> Days;

    /**
     * C++11 polyfill of chrono::weeks
     */
    typedef std::chrono::duration<int64_t, std::ratio<604800>> Weeks;

    /**
     * C++11 polyfill of chrono::months
     */
    typedef std::chrono::duration<int64_t, std::ratio<2629746>> Months;
private:
    tm m_Date;

    static const char TIME_FORMAT[];
    static const char DATE_FORMAT[];
    static const char WHOLE_FORMAT[];
};

#endif //SEM_CDATE_H
