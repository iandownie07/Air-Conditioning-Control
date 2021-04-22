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



#define FIRST_GPIO 2

// This array converts a number 0-9 to a bit pattern to send to the GPIO's
// for 5461BS display
int bits[10] = {0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6};

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
    if (d.day == 31){
        d.day = 0; d.mo++;
        if (d.mo == 13){
            d.mo = 0; d.yr++;
            if (d.yr == 100)
                d.yr = 0;
        }
    }
}

void ClockHour::printTime(){
    while (t.min > 0)
    {
        while (t.seg > 0)
        {
            sleep_ms(750); // sleep for 1 second
            system("clear"); // clear screen
            --t;
            // separate the digits of the countdown for 7 segment
            int digit1 = t.min/10;
            int digit2 = t.min%10;
            int digit3 = t.seg/10;
            int digit4 = t.seg%10;
            int DIG_SOURCE[4] = {digit1, digit2, digit3, digit4};
            //cout << digit1 << digit2 << ":" << digit3 << digit4 << endl;
            
            
            int DIG[4]={10, 11, 12, 13};//The pins used to control the anode of the 4 bit 7 segment, DIG1-DIG4.
            int k = 0;
            int val = 0;
            
            for(k = 0; k < 4; k++)
            {
                gpio_put(DIG[k], 1); // select kth 7 segment
                val = DIG_SOURCE[k];  // select the kth digit
                // We are starting with GPIO 2, our bitmap starts at bit 0 so shift to start at 2.
                int32_t mask = bits[val] << FIRST_GPIO;
                
                // Set all our GPIO's in one go!
                // If something else is using GPIO, we might want to use gpio_put_masked()
                gpio_put_masked(mask, mask);
                sleep_ms(250);
                gpio_clr_mask(mask);
            }
            
            
        }
    }
}

