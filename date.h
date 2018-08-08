#ifndef DATE_H
#define DATE_H


#define DATE_H

#include <math.h>
#include <time.h>
#include <QString>
#include <QCoreApplication>
#include <cstdlib>

class Date {
private:
    int m_DaysSinceBaseDate;
    static int ymd2dsbd(int y, int m, int d);
    void getYMD(int& y, int& m, int& d);
public:
    Date();
    Date(int y, int m, int d);
    void set(int y, int m, int d);
    QString toString(bool brief);
    void setToToday();
    QString getWeekDay();
    bool lessThan(const Date& d);
    bool equals(const Date& d);
    int daysBetween(const Date& d);
    Date addDays(int days);
    static bool leapYear(int year);
    static QString monthName(int month);
    static int yearDays(int year);
    static int monthDays(int month, int year);
    ~Date();
  };

#endif
