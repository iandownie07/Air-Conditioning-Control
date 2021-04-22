//
//  CreateString.h
//  
//
//  Created by Ian Downie on 04/04/21.
//

#ifndef CreateString_h
#define CreateString_h

#include <iostream>
#include <string>

using namespace std;

class Packet
{
    int eventtype_flag;
    string packet, event_time;
    string Yr, Mo, Day, Seg, Min, Hr;
    

    
    
public:
    

    void setEventTime(int nYr, int nMo, int nDay, int nSeg, int nMin, int nHr);
    void setEvent(int);
    void makePacket();
    string getPacket();
    string standardLength(string);
    
};

#endif /* CreateString_h */
