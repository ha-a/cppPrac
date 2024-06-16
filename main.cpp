#include <iostream>
#include "Date.h"
#include "Age.h"
#include "Employee.h"
#include <complex>
#include <string>
#include <cstdio>
#include <iomanip>
#include <regex>

#include <chrono>

void includeGuardTest(){
    Date d(2021, 1, 1);
    std::cout << d.year << std::endl;

    Age a(Date(1999, 2, 2), Date(2024, 6, 19));
    std::cout << a.age << std::endl;

    Employee e(Date(2021, 1, 1), Date(1999, 2, 2), Date(2024, 6, 19));
    std::cout << e.workPeriod.year << " years, " << e.workPeriod.month << " months, " << e.workPeriod.day << " days" << std::endl;

    Employee e2(Date(2021, 1, 1), a);
    std::cout << e2.workPeriod.year << " years, " << e2.workPeriod.month << " months, " << e2.workPeriod.day << " days" << std::endl;
}

#include <vector>

void emplaceBackTest(){
    std::vector<Date> dates;
    dates.emplace_back(2021, 1, 1);
    std::cout << dates[0].year << std::endl;

    std::vector<Employee> employees;
    employees.emplace_back(Date(2024,4,1), Age(Date(1999, 2, 2), Date(2024, 6, 19)));
    std::cout << employees[0].workPeriod.year << " years, " << employees[0].workPeriod.month << " months, " << employees[0].workPeriod.day << " days" << std::endl;
}

#include <unordered_map>
void unorderedMapTest(){
    std::unordered_map<std::string, Date> dateMap;
    dateMap["today"] = Date(2024,6,19);
    dateMap.emplace("birthday", Date(1999,2,2));
    dateMap.emplace(std::piecewise_construct, std::forward_as_tuple("employDay"), std::forward_as_tuple(2024, 4, 1));
}

namespace std{
    template<>
    class hash<Date>{
        public:
        size_t operator()(const Date& d) const{
            return std::hash<int>()(d.year) ^ std::hash<int>()(d.month) ^ std::hash<int>()(d.day);
        }
    };
}

void unorderedMapTest2(){
    using dm = std::unordered_map<Date, std::string>;
    dm dateMap;
    dateMap.insert(dm::value_type(Date(2024,6,19), "today"));
    dateMap.emplace(Date(1999,2,2), "birthday");
    std::cout << dateMap[Date(1999,2,2)] << std::endl;
    // dateMap[Date(2024,6,19)] = "today";
    // dateMap.emplace(Date(1999,2,2), "birthday");
    // dateMap.emplace(Date(2024, 4, 1), "employDay");
    // std::cout << dateMap[Date(2024,6,19)] << std::endl;
}


void vectorAccessTest(){
    std::vector<int> v = {1,2,3};
    for (auto u: v) std::cout << u << ' ';
    std::cout << std::endl;
    // for (int n=0; n<10; ++n) std::cout << v[n] << ' ';
    // std::cout << std::endl;
    // for (int n=0; n<10; ++n) std::cout << v.at(n) << ' ';
    // std::cout << std::endl;
    std::cout << v.size() << std::endl;
}

void arrayTest(){
    int a[3] = {1,2,3};
    size_t n = 3;
    int b[n];
    std::cout << b[0] << std::endl;
}







template <typename T>
T total(const T& v){
    return v;
}
template <typename T>
T total(const std::vector<T>& v) {
    T sum = 0;
    for (const auto& u : v) {
        sum += total(u);
    }
    return sum;
}



int makeSum(int v){
    return v;
}
template <typename T>
int makeSum(const std::vector<T>& v) {
    int sum = 0;
    for (const auto& u : v) {
        sum += makeSum(u);
    }
    return sum;
}


// using person = std::pair<std::string, int>;

struct person{
    std::string name;
    int age;
    bool operator==(const person& p) const{
        return name == p.name && age == p.age;
    }
};
namespace std {
    template<>
    class hash<person> {
        public:
        size_t operator()(const person& p) const {
            return std::hash<std::string>()(p.name) ^ std::hash<int>()(p.age);
        }
    };
}



void compCalcTime(){

    const int sz = 1000;
    auto start = std::chrono::system_clock::now();
    int a[sz][sz]{0};
    for (int n=0; n<sz; ++n)
    {
        for (int m=0; m<sz; ++m)
        {
            a[n][m] = n+m;
        }
    }
    std::cout << a << std::endl;
    std::cout << *a << std::endl;
    for (int n=0; n<sz; ++n)
    {
        for (int m=0; m<sz; ++m)
        {
            ++(a[n][m]);
        }
    }
    std::cout << std::endl;
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> dt = end-start;
    std::cout << dt.count() << " ms" << std::endl;

    start = std::chrono::system_clock::now();
    int (*b)[sz] = new int[sz][sz];
    for (int n=0; n<sz; ++n)
    {
        for (int m=0; m<sz; ++m)
        {
            b[n][m] = n+m;
        }
    }
    std::cout << b << std::endl;
    std::cout << *b << std::endl;
    std::cout << **b << std::endl;
    for (int i=0; i<sz; ++i)
    {
        for (int j=0; j<sz; ++j)
        {
            ++(b[i][j]);
        }
    }
    std::cout << std::endl;
    end = std::chrono::system_clock::now();
    dt = end-start;
    std::cout << dt.count() << " ms" << std::endl;
    delete[] b;
}


// int* returnPtr(int& a){
//     int b = 10;
//     return &b;
// }
// int* returnPtr(){
//     int b[] = {1,2,3};
//     return b;
// }


void myReverse(int* a, size_t n){
    for (size_t i=0; i<n/2; ++i){
        auto v = a[i];
        a[i] = a[n-i-1];
        a[n-i-1] = v;
    }
}
void myReverse(int* start, int* end){
    auto q = end - 1;
    for (int* p=start; p<q; ++p, --q){
        auto v = *p;
        // if (p>=q) break;
        *p = *q;
        *q = v;
    }
}

int main(){
    // includeGuardTest();
    // emplaceBackTest();
    // unorderedMapTest2();
    // vectorAccessTest();

    // arrayTest();

    // std::vector<std::vector<int>> v = {{1,2,3}, {4,5,6}, {7,8,9}};
    // std::vector<int> w = {1,2,3};
    // // std::cout << total(v) << std::endl;
    // // test(w);
    // // int s = 0;
    // // test(s);
    // std::cout << makeSum(v) << std::endl;

    // std::unordered_map<person, int> people;
    // person taro{"Taro", 32};
    // people[taro] = 1;
    // std::cout << people[taro] << std::endl;

    // compCalcTime();

    // int c[3] = {1,2,3};
    // int* p = c;
    // // int** q = &c;
    // int** q = &p;

    // int k = 1;
    // auto s = returnPtr(k);
    // std::cout << *s << std::endl;
    // std::cout << &k << std::endl;
    // auto t = returnPtr();
    // std::cout << *(t+1) << std::endl;


    // std::unordered_map<int,int> dict;
    // dict.find(1)==dict.end() ? dict[0] = 1 : dict[0] = -1;
    // std::cout << dict[0] << std::endl;
    // std::cout << dict[1] << std::endl;
    // dict.find(1)==dict.end() ? dict[0] = 1 : dict[0] = -1;
    // std::cout << dict[0] << std::endl;


    // int k = 1000000;
    // std::unordered_map<int, std::complex<double>> dic;
    // auto start = std::chrono::system_clock::now();
    // for (int n=0; n<k; ++n){
    //     dic[n] = std::complex<double>(n, n+1);
    // }
    // auto end = std::chrono::system_clock::now();
    // std::chrono::duration<double, std::milli> dt = end-start;
    // std::cout << dt.count() << " ms" << std::endl;

    // std::unordered_map<int, std::complex<double>> dic2;
    // start = std::chrono::system_clock::now();
    // for (int n=0; n<k; ++n){
    //     dic2.emplace(std::piecewise_construct, std::forward_as_tuple(n), std::forward_as_tuple(n, n+1));
    // }
    // end = std::chrono::system_clock::now();
    // dt = end-start;
    // std::cout << dt.count() << " ms" << std::endl;


    // int a[] = {1, 2, 3, 4};
    // // myReverse(a, std::end(a)-a);
    // // for (auto u: a) std::cout << u << ' ';
    // // std::cout << std::endl;
    // myReverse(std::begin(a), std::end(a));
    // for (auto u: a) std::cout << u << ' ';
    // std::cout << std::endl;
    
    // std::vector<std::vector<int>> v = {{1,2,3}, {4,5,6}, {7,8,9}};
    // std::cout << makeSum(v) << std::endl;

    // std::string s = "C plus plus";
    // std::cout << s.find("pl") << std::endl;
    // std::cout << s.rfind("pl") << std::endl;
    // // ("朝">"倉")?std::cout<<"true"<<std::endl:std::cout<<"false"<<std::endl;
    // std::cout << s.c_str() << std::endl;
    // auto p = s.c_str();
    // for (auto q=p; *q!='\0'; ++q){
    //     std::cout << *q;
    // }
    // std::cout << std::endl;
    // std::cout << (p+10) << std::endl;

    // char cstr[] = "C plus";
    // std::cout << (cstr+3) << std::endl;
    // std::cout << cstr[3] << std::endl;

    // std::string s2 = cstr;
    // // std::cout << s2 << std::endl;
    // printf("%d\n", std::addressof(p[0]));
    // printf("%d\n", p);

    // // char* q = s.c_str();

/*
    char cstr[] = "C plus";
    std::cout << cstr[2] << std::endl;
    std::cout << *(cstr+2) << std::endl;
    cstr[2] = 'P';
    std::cout << cstr << std::endl;
    printf("%p\n", cstr);
    printf("%p\n", std::addressof(cstr[0]));


    // char* p = "Hello, World!"; // 警告
    const char* p = "C Plus";
    std::cout << p << std::endl;
    printf("%p\n", p);
    // p[0] = 'h'; // セグメンテーション違反

    std::string str = "hoge";
    const char* q = str.c_str();
    std::cout << q << std::endl;

    // char cstr2[] = str.c_str();


    // int a[] = {1,2,3};
    // // a = {4,5,6};
    // a[0] = 4;

    std::cout << std::setw(10) << 123 << std::endl;
    std::cout << std::showpoint << std::uppercase << std::hex << 1234 << std::dec << std::endl;
    std::cout << std::showpos << std::showpoint << 1234. << std::endl;
    std::cout << 1234. << std::flush;
    std::cout << std::endl;
    std::cout << 1234 << ' ' << 5678 << 1234 << std::endl;
    
    // std::string ss;
    // std::cin >> std::ws >> ss;
    // std::cout << ss << std::endl;


    std::cout << std::setiosflags(std::ios_base::boolalpha | std::ios_base::showbase)
              << true << " " << std::hex << 100 << std::endl;

    std::cout << std::setfill('0') << std::setw(10) << 123 << std::endl;

*/

    // std::regex rx(R"(^(?=.*[0-9])(?=.*[A-Z])(?=.*[.@?/-])[a-zA-Z0-9.@?/-]{8,24}$)");
    // std::string s = "P@ssword";
    // std::cout << std::boolalpha << std::regex_match(s, rx) << std::endl;

    // std::regex rg(R"(^(19|20)[0-9]{2}\\(1|)[0-9]$)"); 
    // std::string s2 = "2021\\19";
    // std::cout << std::boolalpha << std::regex_match(s2, rg) << std::endl;
    // std::cout << s2 << std::endl;

    // std::string s = "123-456-789";
    // std::regex rx(R"((\d{3})-(\d{3})-(\d{3}))");
    // std::string t = std::regex_replace(s, rx, "$0/$1"); // "123-456-789" -> "123-789-789"
    // std::cout << t << std::endl;

    // std::string s = "123-456-789";
    // std::regex rx(R"(\d{3})");
    // std::sregex_iterator it(s.begin(), s.end(), rx);
    // std::sregex_iterator end;
    // while (it != end){
    //     std::cout << (it++)->str() << std::endl; // 123, 456, 789
    // }

    // std::string s = "a-b2-c3+d4";
    // std::regex t{"(-)([a-z])([0-9])"};
    // for (std::sregex_token_iterator e, i{begin(s), end(s), t, 0}; i != e; ++i)
    // std::cout << *i << ", "; // 出力順: "-b", "-c"
    // std::cout << std::endl;
    // for (std::sregex_token_iterator e, i{begin(s), end(s), t, 1}; i != e; ++i)
    // std::cout << *i << ", "; // 出力順: "-" , "-"
    // std::cout << std::endl;
    // for (std::sregex_token_iterator e, i{begin(s), end(s), t, 3}; i != e; ++i)
    // std::cout << *i << ", "; // 出力順: "b" , "c"
    // std::cout << std::endl;
    // for (std::sregex_token_iterator e, i{begin(s), end(s), t, -1}; i != e; ++i)
    // std::cout << *i << ", "; // 出力順: "a", "+d"
    // std::cout << std::endl;


    std::string s = "123-456-789";
    std::regex rx(R"((-)([0-9]))");
    
    std::sregex_token_iterator it0(s.begin(), s.end(), rx, 0);
    std::sregex_token_iterator end;
    while (it0 != end)  std::cout << (it0++)->str() << ", "; // -4, -7
    
    std::sregex_token_iterator it2(s.begin(), s.end(), rx, 2);
    while (it2 != end)  std::cout << (it2++)->str() << ", "; // 4, 7
    
    std::sregex_token_iterator it(s.begin(), s.end(), rx, -1);
    while (it != end)  std::cout << (it++)->str() << ", "; // 123, 56, 89

   return 0;
}