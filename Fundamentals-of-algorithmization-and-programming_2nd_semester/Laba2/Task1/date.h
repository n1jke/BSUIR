#ifndef DATE_H
#define DATE_H
#include <QVector>
#include "magic.h"

class Date {
    int day_;
    int month_;
    int year_;
    int day_of_year_ = kZero;
    QVector<int> days_in_month_ = kDaysInMonth;

   public:
    Date();
    Date(int, int, int);
    QString fromDateToString();

    bool isLeap();
    Date NextDay();
    Date PreviousDay();
    int WeekNumber();
    int countDays(const Date&);
    bool isValid();
    Date currentDate();
    int daysTillYourBithday(Date& birthday_date);
    int duration(const Date& end_date, const Date& start_date);
    int duration(Date& end_date);
};

#endif	// DATE_H
