//
//  ClockHour.cpp
//  
//
//  Created by Ian Downie on 01/04/21.
//

#include <stdio.h>
#include "ClockTime.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"

// sets and gets for the time

void ClockHour::setHr(int nhr){
    hr = nhr;
}

void ClockHour::setMin(int nmin){
    min = nmin;
}

void ClockHour::setSeg(int nseg){
    seg = nseg;
}

void ClockDate::setYr(int nyr){
    yr = nyr;
}

void ClockDate::setMo(int nmo){
    mo = nmo;
}

void ClockDate::setDay(int nday){
    day = nday;
}

int ClockHour::getHr(){
    return hr;
}

int ClockHour::getMin(){
    return min;
}

int ClockHour::getSeg(){
    return seg;
}

int ClockDate::getYr(){
    return yr;
}

int ClockDate::getMo(){
    return mo;
}

int ClockDate::getDay(){
    return day;
}

// Overloading of << operator. Useful for debugging
ostream& operator<< (ostream& c, ClockHour t){
    c << t.hr << ":";
    c << t.min << ":";
    c << t.seg;
    return c;
}

ostream& operator<< (ostream& c, ClockDate d){
    c << d.day << ":";
    c << d.mo << ":";
    c << d.yr;
    return c;
}

// Overloading of operators -- and ++, used to count the time and date
// the methods implement the rules for these calculations
void operator-- (ClockHour& t){
    t.seg--;
    if (t.seg == 0 && t.min != 0){
        t.seg = 59; t.min--;
    }
}

void operator++ (ClockHour& t){
    t.seg++;
    if (t.seg == 60){
        t.seg = 0; t.min++;
        if (t.min == 60){
            t.min = 0; t.hr++;
            if (t.hr == 24)
                t.hr = 0;
        }
    }
}

void operator++ (ClockDate& d){
    d.day++; // I need to change the day when t.hr = 0
    if (d.day == 31){ // Simplified so that all months have 30 days
        d.day = 0; d.mo++;
        if (d.mo == 13){
            d.mo = 0; d.yr++;
            if (d.yr == 100)
                d.yr = 0;
        }
    }
}


