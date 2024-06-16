#ifndef DATE_H
#define DATE_H

class Date{
public:
    int year;
    int month;
    int day;
    Date(): year(0), month(0), day(0){}
    Date(int y, int m, int d): year(y), month(m), day(d){}
    bool operator==(const Date& d) const{
        return year == d.year && month == d.month && day == d.day;
    }
};

#endif