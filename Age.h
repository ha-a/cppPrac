#pragma once

#include "Date.h"

class Age{
public:
    Date birthDay;
    Date today;
    int age;
    Age(Date b, Date t): birthDay(b), today(t){
        age = today.year - birthDay.year;
        if (today.month < birthDay.month || (today.month == birthDay.month && today.day < birthDay.day)){
            age -= 1;
        }
    }
};
