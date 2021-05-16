//
//  ClockTime.h
//
//
//  Created by Ian Downie on 03/04/21.
//

#ifndef ClockTime_h
#define ClockTime_h

#include <iostream>
#include <unistd.h> // library that includes "sleep"
using namespace std;

class ClockHour {
public:
    int hr;
    int min;
    int seg;
    void setHr(int);
    void setMin(int);
    void setSeg(int);
    int getHr();
    int getMin();
    int getSeg();
    friend ostream& operator<< (ostream&, ClockHour);
    friend void operator++ (ClockHour&);
    friend void operator-- (ClockHour&);
};

class ClockDate {
public:
    int mo;
    int day;
    int yr;
    void setYr(int);
    void setMo(int);
    void setDay(int);
    int getYr();
    int getMo();
    int getDay();
    friend ostream& operator<< (ostream&, ClockDate);
    friend void operator++ (ClockDate&);
};
#endif /* ClockTime_h */
