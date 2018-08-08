#include "date.h"

static int baseyear = 1900;
Date::Date(){
    set( 1900, 1, 1);
}

Date::~Date(){}

Date::Date(int y, int m, int d){
   set(y,m,d);
}

void Date::set(int y, int m, int d){
    m_DaysSinceBaseDate=ymd2dsbd(y,m,d);
}

void Date::setToToday() {
  struct tm *tp = 0;
  time_t now;
  now = time(0);
  tp = localtime(&now);
  return set(1900 + tp->tm_year, 1 + tp->tm_mon, tp->tm_mday);
}

int Date::ymd2dsbd(int y, int m, int d){
      //base date is January 1, 1900
    int year_days = 0;
    int month_days=0;
    for (int i=baseyear;i<y;i++){
        year_days = year_days+ yearDays(i);
    }
    for (int j=1;j<m;j++){
        month_days = month_days+ monthDays(j,y);
    }
    return year_days+month_days+d;
}

void Date::getYMD(int& y, int& m, int& d){
    //base date is January 1,1900
       int extra_days = 0;
       int year = (m_DaysSinceBaseDate/365)+baseyear;
       for (int i=baseyear;i<year;i++){
           if (leapYear(i)==true){
               extra_days = extra_days+1;
           }
       }

       int actual_days = m_DaysSinceBaseDate-extra_days;
       int remaining_days= actual_days%365;
       bool check_leapyear = leapYear(year);
       int month=1;
       if (check_leapyear==true){
           while(remaining_days>29){
               remaining_days=remaining_days-monthDays(month,year);
               month=month+1;
           }
        }else{
           while(remaining_days>31){
               remaining_days=remaining_days-monthDays(month,year);
               month=month+1;
           }
       }

       y=year;
       m=month;
       d=remaining_days;

}

QString Date::toString(bool brief){
    //base date is January 1,1900
    int year =0;
    int month=0;
    int days=0;
    getYMD(year,month,days);

    if (brief==true){
        return(QString::number(month)+"/"+QString::number(days)+"/"+QString::number(year));
    }else{
        return(QString::number(year)+"-"+QString::number(month)+"-"+QString::number(days));

    }

}

QString Date::getWeekDay(){
    int year=0;
    int month=0;
    int days=0;
    getYMD(year,month,days);

    int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
       year -= month < 3;
       int weekday= ( year + year/4 - year/100 + year/400 + t[month-1] + days) % 7;
    switch(weekday){
        case 1: return "Monday";
        case 2: return "Tuesday";
        case 3: return "Wednesday";
        case 5: return "Thursday";
        case 4: return "Friday";
        case 6: return "Saturday";
        default: return "Sunday";

    }

}

bool Date::lessThan(const Date& d){
    return (d.m_DaysSinceBaseDate<m_DaysSinceBaseDate);

}


bool Date::equals(const Date& d){
    return (d.m_DaysSinceBaseDate==m_DaysSinceBaseDate);
}

int Date::daysBetween(const Date& d){
    return abs(d.m_DaysSinceBaseDate-m_DaysSinceBaseDate);
}

Date Date::addDays(int days){
    int extra_days = 0;
    m_DaysSinceBaseDate = m_DaysSinceBaseDate+days;
    int year = (m_DaysSinceBaseDate/365)+baseyear;
    for (int i=baseyear;i<year;i++){
        if (leapYear(i)==true){
            extra_days = extra_days+1;
        }
    }

    int actual_days = m_DaysSinceBaseDate-extra_days;
    int remaining_days= actual_days%365;
    bool check_leapyear = leapYear(year);
    int month=1;
    if (check_leapyear==true){
        while(remaining_days>29){
            remaining_days=remaining_days-monthDays(month,year);
            month=month+1;
        }
     }else{
        while(remaining_days>31){
            remaining_days=remaining_days-monthDays(month,year);
            month=month+1;
        }
    }
   return Date(year,month,remaining_days);

}

bool Date::leapYear(int year){
    if (((year % 4 == 0) && !(year % 100 == 0))|| (year % 400 == 0))
        return true;
    else
        return false;
}

QString Date::monthName(int month){
    switch (month){
        case 1: return "January";
        case 2: return "February";
        case 3: return "March";
        case 4: return "April";
        case 5: return "May";
        case 6: return "June";
        case 7: return "July";
        case 8: return "August";
        case 9: return "September";
        case 10: return "October";
        case 11: return "November";
        case 12: return "December";
        default: return "Invalid!";

    }
}

int Date::yearDays(int year){
    if (leapYear(year)==true)
        return 366;
    else
        return 365;

}

int Date::monthDays(int month, int year){
    if (leapYear(year)==true){
        switch (month){
        case 1: return 31;
        case 3: return 31;
        case 5: return 31;
        case 7: return 31;
        case 8: return 31;
        case 10:return 31;
        case 12:return 31;
        case 2: return 29;
        default: return 30;
        }
    }else{
        switch (month){
        case 1: return 31;
        case 3: return 31;
        case 5: return 31;
        case 7: return 31;
        case 8: return 31;
        case 10:return 31;
        case 12:return 31;
        case 2: return 28;
        default: return 30;

        }

    }
}

