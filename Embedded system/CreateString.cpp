//
//  CreateString.cpp
//
//
//  Created by Ian Downie on 04/04/21.
//

#include "CreateString.h"




void Packet::setEventTime(int nYr, int nMo, int nDay, int nSeg, int nMin, int nHr)
{
    
    Yr = standardLength(to_string(nYr)); Mo = standardLength(to_string(nMo));  Day = standardLength(to_string(nDay));
    Seg = standardLength(to_string(nSeg)); Min = standardLength(to_string(nMin)); Hr = standardLength(to_string(nHr));
    
    event_time = Hr+Min+Seg+Day+Mo+Yr;
}

void Packet::setEvent(int neventtype_flag)
{
    eventtype_flag = neventtype_flag;
}

void Packet::makePacket()
{
    if (eventtype_flag == 1)
        event_flag = '1';
    if (eventtype_flag == 2)
        event_flag = '2';
    if (eventtype_flag == 3)
        event_flag = '3';
    
    
    
    event_time.push_back(event_flag);
    char end = 'e';
    event_time.push_back(end);
    string code = "1875";
    event_time.insert(0, code);// hot-tub code
    packet = event_time;
}

string Packet::getPacket()
{
    return packet;
}

string Packet::standardLength(string input_string)
{
    if (input_string.size() == 1)
    {
        string add_zero = "0";
        input_string.insert(0, add_zero);
    }
    return input_string;
}

/*
 int main ()
 {
 Packet pack;
 string output;
 pack.setStoph_Flag(false);
 pack.setStarth_Flag(true);
 pack.setEvent(1);
 pack.setEventTime(16, 5, 21, 50, 54, 16);
 pack.makePacket();
 output = pack.getPacket();
 cout << output << endl;
 }
 
 */
