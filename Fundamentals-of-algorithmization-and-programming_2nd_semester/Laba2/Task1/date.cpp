#include "date.h"
#include <ctime>

Date::Date() {
    day_ = kOne;
    month_ = kOne;
    year_ = kOne;
}

Date::Date(int day, int month, int year) {
    day_ = day;
    month_ = month;
    year_ = year;
    if (!isValid()) {
        day_ = kOne;
        month_ = kOne;
        year_ = kDefaultYear;
    }


    for (int i = 0; i <= month - 1; ++i) {
        day_of_year_ += days_in_month_[i];
    }
    if (isLeap() && month >= 2) {
        ++day_of_year_;
    }
}

bool Date::isLeap() {
    return (year_ % kFour == 0) &&
           (year_ % kOneHundred != 0 || year_ % kFourHundred == 0);
}

Date Date::PreviousDay() {


    if (day_ > 1) {
        return Date(day_ - 1, month_, year_);
    } else if (month_ > 1) {
        int prev_month = month_ - 1;
        int prev_day = days_in_month_[prev_month - 1];
        if (prev_month == 2 && isLeap()) {
            prev_day = kDaysInFebruaryLeap;
        }
        return Date(prev_day, prev_month, year_);
    } else {
        return Date(kThirtyOne, kTwelve, year_ - 1);
    }
}

Date Date::NextDay() {
    int days_in_current_month = days_in_month_[month_ - 1];
    if (month_ == 2 && isLeap()) {
        days_in_current_month = kDaysInFebruaryLeap;
    }


    if (day_ < days_in_current_month) {
        return Date(day_ + 1, month_, year_);
    } else if (month_ < kTwelve) {
        return Date(1, month_ + 1, year_);
    } else {
        return Date(1, 1, year_ + 1);
    }
}

int Date::WeekNumber() {
    return day_of_year_ / kSeven;
}

QString Date::fromDateToString() {
    if (!isValid()) {
        return "Invalid date";
    }

    QString day_str =
        (day_ < kTen) ? "0" + QString::number(day_) : QString::number(day_);
    QString month_str = (month_ < kTen) ? "0" + QString::number(month_)
                                        : QString::number(month_);
    QString year_str = QString::number(year_);

    return day_str + "." + month_str + "." + year_str;
}

/*
int Date::countDays(const Date& x) {
    long long result = 0;


    for (int y = 1; y <= x.year_; ++y) {
        if ((y % 4 == 0) && (y % kOneHundred != 0 || y % kFourHundred == 0)) {
            result += kLeapYearDays;
        } else {
            result += kCommonYearDays;
        }
    }


    for (int y = 1; y <= x.month_; ++y) {
        if ((y % 4 == 0) && (y % kOneHundred != 0 || y % kFourHundred == 0) &&
            y == 2) {
            result += kDaysInFebruaryLeap;
        } else {
            result += days_in_month_[y - 1];
        }
    }
    result += x.day_;
    return result;
}
*/


long long julianDay(int day, int month, int year) {
    if (month < 3) {
        year -= 1;
        month += kTwelve;
    }
    int a = year / kOneHundred;
    int b = a / 4;
    int c = 2 - a + b;
    int e = static_cast<int>(kJKalender * (year + kStartJul));
    int f = static_cast<int>(kJMonth * (month + 1));
    long long jd = c + day + e + f - kJul;
    return jd;
}

int Date::duration(const Date& end_date, const Date& start_date) {
    long long start_jd =
        julianDay(start_date.day_, start_date.month_, start_date.year_);
    long long end_jd =
        julianDay(end_date.day_, end_date.month_, end_date.year_);
    return static_cast<int>(end_jd - start_jd);
    /*
    auto days_since_epoch = [](Date d) {
        int days = 0;


        for (int y = 1; y < d.year_; ++y) {
            days +=
                (y % 4 == 0 && (y % kOneHundred != 0 || y % kFourHundred == 0))
                    ? kLeapYearDays
                    : kCommonYearDays;
        }


        for (int m = 1; m < d.month_; ++m) {
            days += d.days_in_month_[m - 1];
            if (m == 2 && d.isLeap()) {
                days += 1;
            }
        }
        days += d.day_ - 1;
        return days;
    };

    int start_days = days_since_epoch(std::move(start_date));  // enjoy linter)
    int end_days = days_since_epoch(std::move(end_date));
    return end_days - start_days;
*/
}

bool Date::isValid() {


    if (month_ < 1 || month_ > kTwelve) {
        return false;
    }
    int days_in_month = days_in_month_[month_ - 1];
    if (month_ == 2 && isLeap()) {
        days_in_month = kDaysInFebruaryLeap;
    }
    return day_ >= 1 && day_ <= days_in_month && year_ > 0;
}

int Date::duration(Date& end_date) {
    return duration(end_date, *this);
}

int Date::daysTillYourBithday(Date& birthday_date) {
    Date current = *this;
    Date next_bday(birthday_date.day_, birthday_date.month_, current.year_);

    bool is_before = false;


    if (next_bday.year_ < current.year_) {
        is_before = true;
    } else if (next_bday.year_ == current.year_) {
        if (next_bday.month_ < current.month_) {
            is_before = true;
        } else if (next_bday.month_ == current.month_) {
            if (next_bday.day_ < current.day_) {
                is_before = true;
            }
        }
    }


    if (is_before) {
        next_bday =
            Date(birthday_date.day_, birthday_date.month_, current.year_ + 1);
    }

    return duration(next_bday, current);
}

Date Date::currentDate() {
    std::time_t t = std::time(nullptr);	 // from 1 january 1970 (unix-time)
    std::tm* now = std::localtime(&t);	 // parse to struct by tear, month ..
    return Date(now->tm_mday, now->tm_mon + 1,
                now->tm_year +
                    kYearBase);	 // month + 1 thow numeration from 0 in time_t
}
