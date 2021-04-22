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


void Event::printEvent()
{
    static volatile bool header_index = true;
    
    while (header_index)
    {
        cout << "Event Type = 0: system start up from mains" << endl;
        cout << "Event Type = 1: system turned off due to time out" << endl;
        cout << "Event Type = 2: button press when system was off" << endl;
        cout << "Event Type = 3: button press when system was operating" << endl;
        cout << "Hot-tub Code   Event Time  Event Date   Stop Event   Start Event   Event Type  Period of Day" << endl;
        
        cout << endl;
        header_index = false;
    }
    cout << eventCodes.codes.hottub_code1 << "            " << timeDate.tempo.hr << ":" << timeDate.tempo.min << ":" << timeDate.tempo.sec << "   "<< timeDate.data.day << "/" << timeDate.data.mo << "/" << timeDate.data.yr << "         " << eventCodes.codes.event_flag1 << "           " << eventCodes.codes.period_of_day << endl;
}

void Event::selectByDateRange(int* yr1, int* mn1, int* dy1, int* yr2, int* mn2, int* dy2)
{
    
    
    if(*yr1 == *yr2)
    {
        if(*mn1 == *mn2)
        {
            if(*dy1 <= timeDate.data.day && timeDate.data.day <= *dy2)
                printEvent();
        }
    }
    else if (*yr1 == *yr2)
    {
        if(*mn1 <= timeDate.data.mo && timeDate.data.mo <= *mn2)
        {
            printEvent();
        }
    }
    else if(*yr1 <= timeDate.data.yr && timeDate.data.yr <= *yr2)
    {
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


void Event::calculateTotalHeaterUse(Event* pevent, int* yr1, int* mn1, int* dy1, int* yr2, int* mn2, int* dy2, int length)
{
    static std::vector<Event*> heaterEvents;
    if(*yr1 == *yr2)
    {
        if(*mn1 == *mn2)
        {
            if(*dy1 <= timeDate.data.day && timeDate.data.day <= *dy2)
            heaterEvents.push_back(pevent);
        }
    }
    
    else if (*yr1 == *yr2)
    {
        if(*mn1 <= timeDate.data.mo && timeDate.data.mo <= *mn2)
            heaterEvents.push_back(pevent);
    }
    
    else if(*yr1 <= timeDate.data.yr && timeDate.data.yr <= *yr2)
    {
        heaterEvents.push_back(pevent);
    }
    
    if(length == 0)
    {
        int totaltime = 0;
        
        for(int i = 0; i < heaterEvents.size(); i++)
           // if(heaterEvents[i]->eventCodes.codes.stop_flag1 && heaterEvents[i+1]->eventCodes.codes.start_flag1)
            {
                //calculate the time difference
                
                struct tm t1, t2;
                time_t time_1, time_2;
                
                t1.tm_year = heaterEvents[i]->timeDate.data.yr + 2000 - 1900;
                t1.tm_mon = heaterEvents[i]->timeDate.data.mo;
                t1.tm_mday = heaterEvents[i]->timeDate.data.day;
                t1.tm_hour = heaterEvents[i]->timeDate.tempo.hr;
                t1.tm_min = heaterEvents[i]->timeDate.tempo.min;
                t1.tm_sec = heaterEvents[i]->timeDate.tempo.sec;
                time_1 = mktime(&t1);
                
                t2.tm_year = heaterEvents[i+1]->timeDate.data.yr + 2000 - 1900;
                t2.tm_mon = heaterEvents[i+1]->timeDate.data.mo;
                t2.tm_mday = heaterEvents[i+1]->timeDate.data.day;
                t2.tm_hour = heaterEvents[i+1]->timeDate.tempo.hr;
                t2.tm_min = heaterEvents[i+1]->timeDate.tempo.min;
                t2.tm_sec = heaterEvents[i+1]->timeDate.tempo.sec;
                time_2  = mktime(&t2);
                time_t tt1, tt2;
                
                cout << "Stop time is " << ctime(&time_1) << endl;
                cout << "Start time is " << ctime(&time_2) << endl;
                
                tt1 = mktime(&t1);
                tt2 = mktime(&t2);
                int time_difference = tt1 - tt2;
                totaltime = totaltime + time_difference;
                //cout << "The total time is " << time_difference << endl;
                int hour = time_difference/3600;
                time_difference = time_difference%3600;
                int minute = time_difference/60;
                time_difference = time_difference%60;
                int second = time_difference;
                
                cout << "The total time is " << hour << ":" << minute << ":" << second << endl;

                
            }
        int hour = totaltime/3600;
        totaltime = totaltime%3600;
        int minute = totaltime/60;
        totaltime = totaltime%60;
        int second = totaltime;
        cout << "the total time heater was in use was " << hour << " hours " << minute << " minutes and " << second << " seconds" <<endl;
    }
   // delete pevent;
}
