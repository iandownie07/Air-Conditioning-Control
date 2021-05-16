//
//  Event.h
//  
//
//  Created by Ian Downie on 06/04/21.
//

#ifndef Event_h
#define Event_h

#include <string>

using namespace std;

// structures for each data type
typedef struct
{
    int mo, day, yr;
} data_t;

typedef struct
{
    int hr, min, sec;
} tempo_t;

typedef struct
{
    int hottub_code1, event_flag1, event_index;
    string period_of_day;
} codes_c;



class Clock
{
public:
    tempo_t tempo;
    void setClock(int h, int m, int s);
    tempo_t& getClock();
};

class Calendar
{
public:
    data_t data;
    void setCalendar(int m, int d, int y);
    data_t& getCalendar();
};

class ClockCalendar : public Clock, public Calendar
{
public:
    // void calculateTimeDifference();
};

class Codes
{
public:
    codes_c codes;
    void setCodes(int , int, string, int);
    
};

class Event
{

    static unsigned int morning_count, afternoon_count, night_count;
public:
    
    Codes eventCodes;
    ClockCalendar timeDate;
    void printEvent();
    void selectByDateRange(int*, int*, int*, int*, int*, int*);
    void selectByTimeOfDay(int);
    void calculateTotalAirConUse(Event* pevent,  int* yr1, int* mn1, int* dy1, int* yr2, int* mn2, int* dy2, int);
};
#endif /* Event_h */
