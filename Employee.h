

#include "Date.h"
#include "Age.h"
class Employee{
    public:
    Date employDay;
    Age age;
    Date workPeriod;
    
    Employee(Date e, Date b, Date t): employDay(e), age(b, t){
        calcWorkPeriod(e, t);
    }
    Employee(Date e, Age a): employDay(e), age(a){
        calcWorkPeriod(e, a.today);
    }

    void calcWorkPeriod(Date e, Date t){
        int year = t.year - e.year;
        int month = t.month - e.month;
        int day = t.day - e.day;
        if (month < 0 || (month == 0 && day < 0)){
            year -= 1;
            if (month < 0){
                month += 12;
            }
            if (day < 0){
                day += 30;
            }
        }
        workPeriod = Date(year, month, day);
    }

};