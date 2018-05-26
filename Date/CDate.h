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
    int getYear() const;

    /**
     * @return Month of date. Integer 1-12.
     */
    int getMonth() const;

    /**
     * @return Day of date. Integer 1-31 (depending on month).
     */
    int getDay() const;
    /**
     * @return Hour of date. Integer 0-23.
     */
    int getHour() const;

    /**
     * @return Minute of date. Integer 0-59.
     */
    int getMinute() const;

    /**
     * @return time_t value. Useful for date arithmetics.
     */
    time_t Count() const;

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

    /**
     * Adds one month to date. Check for invalid dates must be
     * done manually i. e. 29. 1. 2001 + Month will throw error.
     * Year overflows automatically.
     * @return CDate with one more month.
     */
    CDate nextMonth() const;

    friend std::ostream & operator << (std::ostream & stream, const CDate & date);

    /**
     * C++11 polyfill of chrono::days
     */
    typedef std::chrono::duration<int64_t, std::ratio<86400>> Days;

    /**
     * C++11 polyfill of chrono::weeks
     */
    typedef std::chrono::duration<int64_t, std::ratio<604800>> Weeks;
private:
    tm m_Date;

    static const char TIME_FORMAT[];
    static const char DATE_FORMAT[];
};

#endif //SEM_CDATE_H
