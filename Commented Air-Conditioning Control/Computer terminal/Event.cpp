//
//  Event.cpp
//
//
//  Created by Ian Downie on 06/04/21.
//

#include "Event.h"
#include <iostream>
#include <vector>


using namespace std;


// sets for times and codes
void Clock::setClock(int h, int m, int s)
{
    tempo.hr = h;
    tempo.min = m;
    tempo.sec = s;
}

void Calendar::setCalendar(int d, int m, int y)
{
    data.day = d;
    data.mo = m;
    data.yr = y;
}

void Codes::setCodes(int nhottub_code,  int nevent_flag, string nperiod_of_day, int nevent_index)
{
    codes.hottub_code1 = nhottub_code;
    codes.event_flag1 = nevent_flag;
    codes.period_of_day = nperiod_of_day;
    codes.event_index = nevent_index;
}

//General print method for event table
void Event::printEvent()
{
    static volatile bool header_index = true;
    
    while (header_index)
    {
        cout << "Event Type = 1: system disconnection" << endl;
        cout << "Event Type = 2: button press" << endl;
        cout << "Event Type = 3: system connection" << endl;
        cout << endl;
        cout << "Air Con Code   Event Time  Event Date  Event Type  Period of Day" << endl;
        
        cout << endl;
        header_index = false;
    }
    cout << eventCodes.codes.hottub_code1 << "          " << timeDate.tempo.hr << ":" << timeDate.tempo.min << ":" << timeDate.tempo.sec << "     "<< timeDate.data.day << "/" << timeDate.data.mo << "/" << timeDate.data.yr << "         " << eventCodes.codes.event_flag1 << "           " << eventCodes.codes.period_of_day << endl;
}

// Select event by date
void Event::selectByDateRange(int* yr1, int* mn1, int* dy1, int* yr2, int* mn2, int* dy2)
{
    // Filter by day
    if((*yr1 == *yr2) && (*mn1 == *mn2) && (*dy1 <= timeDate.data.day && timeDate.data.day <= *dy2))
    {
        //cout << timeDate.data.day << " day added" << endl;
        printEvent();
    }
    
    // Filter by month
    else if ((*yr1 == *yr2) && (*mn1 <= timeDate.data.mo && timeDate.data.mo <= *mn2))
    {
        //cout << timeDate.data.mo << " month added" << endl;
        printEvent();
    }
    
    // Filter by year
    else if(*yr1 <= timeDate.data.yr && timeDate.data.yr <= *yr2 && *yr1 < *yr2)
    {
        //cout << timeDate.data.yr << " year added" << endl;
        printEvent();
    }
}

void Event::selectByTimeOfDay(int length)
{
    static unsigned int morning_count, afternoon_count, night_count;
    
    if (eventCodes.codes.period_of_day == "morning")
        morning_count++;
    if (eventCodes.codes.period_of_day == "afternoon")
        afternoon_count++;
    if (eventCodes.codes.period_of_day == "night")
        night_count++;
    if(length == 0)
    {
        cout << "The control-system event total was " << morning_count << " from 4am to 12pm" << endl;
        cout << "The control-system event total was " << afternoon_count << " from 12pm to 8pm" << endl;
        cout << "The control-system event total was " << night_count << " from 8pm to 4am" << endl;
    }
}


void Event::calculateTotalAirConUse(Event* pevent, int* yr1, int* mn1, int* dy1, int* yr2, int* mn2, int* dy2, int length)
{
    //cout << "length in calculate is " << length << endl;
    // Filter events
    static std::vector<Event*> airConEvents;
    if((*yr1 == *yr2) && (*mn1 == *mn2) && (*dy1 <= timeDate.data.day && timeDate.data.day <= *dy2))
    {
        airConEvents.push_back(pevent); // add events to vector "airConEvents"
        //cout << timeDate.data.day << " day added" << endl;
    }
    
    else if ((*yr1 == *yr2) && (*mn1 <= timeDate.data.mo && timeDate.data.mo <= *mn2))
    {
        airConEvents.push_back(pevent);
        //cout << timeDate.data.mo << " month added" << endl;
    }
    
    else if(*yr1 <= timeDate.data.yr && timeDate.data.yr <= *yr2 && *yr1 < *yr2)
    {
        airConEvents.push_back(pevent);
        //cout << timeDate.data.yr << " year added" << endl;
    }
    
    if(length == 0)
        // Enter condition once all events have been filtered
    {
        int totaltime = 0;
        //cout << "Vector size is " << airConEvents.size() << endl;
        for(int i = 0; i < airConEvents.size(); i++)
        {
           if(airConEvents[i]->eventCodes.codes.event_flag1 == 1 && airConEvents[i+1]->eventCodes.codes.event_flag1 == 3)
               // if this event is a stop event and the previous event was a start event, calculate the time between them
            {
                //calculate the time difference
                struct tm t1, t2;
                time_t time_1, time_2;
                
                t1.tm_year = airConEvents[i]->timeDate.data.yr + 2000 - 1900;
                t1.tm_mon = airConEvents[i]->timeDate.data.mo;
                t1.tm_mday = airConEvents[i]->timeDate.data.day;
                t1.tm_hour = airConEvents[i]->timeDate.tempo.hr;
                t1.tm_min = airConEvents[i]->timeDate.tempo.min;
                t1.tm_sec = airConEvents[i]->timeDate.tempo.sec;
                time_1 = mktime(&t1);
                
                t2.tm_year = airConEvents[i+1]->timeDate.data.yr + 2000 - 1900;
                t2.tm_mon = airConEvents[i+1]->timeDate.data.mo;
                t2.tm_mday = airConEvents[i+1]->timeDate.data.day;
                t2.tm_hour = airConEvents[i+1]->timeDate.tempo.hr;
                t2.tm_min = airConEvents[i+1]->timeDate.tempo.min;
                t2.tm_sec = airConEvents[i+1]->timeDate.tempo.sec;
                time_2  = mktime(&t2);
                time_t tt1, tt2;
                
                //cout << "Stop time is " << ctime(&time_1) << endl;
                //cout << "Start time is " << ctime(&time_2) << endl;
                
                tt1 = mktime(&t1);
                tt2 = mktime(&t2);
                int time_difference = tt1 - tt2;
                totaltime = totaltime + time_difference; // add calculated time difference to total time
                //cout << "The total time is " << time_difference << endl;
                int hour = time_difference/3600;
                time_difference = time_difference%3600;
                int minute = time_difference/60;
                time_difference = time_difference%60;
                int second = time_difference;
                
                //cout << "The total time is " << hour << ":" << minute << ":" << second << endl;
            }
        }
        int hour = totaltime/3600;
        totaltime = totaltime%3600;
        int minute = totaltime/60;
        totaltime = totaltime%60;
        int second = totaltime;
        cout << "The total time air conditioning was in use was " << hour << " hours " << minute << " minutes and " << second << " seconds" <<endl;
        airConEvents.clear();
    }
   // delete pevent;
}
