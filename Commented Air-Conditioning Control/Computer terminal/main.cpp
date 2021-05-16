//  main.cpp

// A serial port utility for MacOS X

// For communicating with serial devices (e.g. microcontrollers)
// usually via USB serial.

//Includes
#include "Event.cpp"
#include "List.cpp"
#include "SerialPort.hpp"
#include "SerialPort.cpp"
#include "TypeAbbreviations.hpp"
#include <iostream>
#include <string>
#include "unistd.h"

using namespace std;

int main(int argc, const char * argv[]) {
    // optional procedure in case we want to introduce password-controlled access
    /* string password;
     
     cout << "Please type your password" << endl;
     cin >> password;
     
     while(password != "password")
     {
     cout << "Incorrect. Please type your password again" << endl;
     cin >> password;
     }
     char txchar;
     cout << "To start a data transfer, connect the control system and type 1" << endl;
     cin >> txchar;
     */
    char txchar = '1'; // delete if password control is included
    
    //* Open port, and connect to a device
    const char devicePathStr[] = "/dev/tty.usbserial-A50285BI";
    const int baudRate = 57600;
    // returns -1 if open fails or device code if succeeds
    int sfd = openAndConfigureSerialPort(devicePathStr, baudRate);
    if (sfd < 0) {
        if (sfd == -1) {
            printf("Unable to connect to serial port.\n");
        }
        else { //sfd == -2
            printf("Error setting serial port attributes.\n");
        }
        return 0;
    }
    
    List list1; // create a list
    writeSerialData(&txchar, 1);    // write to serial port to tell external device it's open
    bool transmission = true;   // enter loop
    string period_of_day;   // create a string for period of day
    int event_index = 0; // create event_index to remove duplicate events from button press
    while(transmission)
    {
        // loop to add an event to the linked list from UART transmission
        // receive a transmission
        char rxChar; // each char received
        char lineStr[17]; // 17 without 'e'. All chars will be placed in this vector
        int lineStrIndex=0; // initialise index
        bool stay = true; // bool to decide if the end of a packet has been reached
        while (stay)
        { // receive bytes until byte = e when a packet ends
            //Receive any new data available from the device, byte by byte
            ssize_t byteReceived = readSerialData(&rxChar, 1);
            if (byteReceived < 0) {
                //eLog("readSerialData() failed. Errno:{}", errno); //Or you could use printf; errno is a number (I think...)
                std::cout << "error" << std::endl;
                stay = false;
            }
            
            else if (byteReceived == 0)
            { //Not a failure condition; sometimes you just don't receive anything (or are in the middle of receiving something...)
                stay = true;
                std::cout << "nothing yet" << std::endl;
                // wait for something to enter the UART
                sleep(1);
            }
            
            if (byteReceived > 0)
            {
                
                if((rxChar == '0') || (rxChar == '1') || (rxChar == '2') || (rxChar == '3') || (rxChar == '4') || (rxChar == '5') || (rxChar == '6') || (rxChar == '7') || (rxChar == '8') || (rxChar == '9'))
                    // only add numerical digits to vector
                {
                    //Add byte to line, update index, error-check
                    lineStr[lineStrIndex] = rxChar;
                    //std::cout << "The item is " << lineStr[lineStrIndex] <<
                    //std::endl;
                    //std::cout << "The index is: " << lineStrIndex << std::endl;
                    lineStrIndex++;
                }
                
                if(rxChar =='e') // end of a packet
                    stay = false;
                if(rxChar == 'f')
                {// end of a transmission
                    transmission = false;
                    stay = false;
                    //cout << "end transmission, transmission = " << transmission << endl;
                    //cout << "end transmission, stay = " << stay << endl;
                }
            }
        }
           // now we've recieved the packet, separate the data but keep them all as a new instance of type Event
        // organise data from a packet
        lineStrIndex++;
        char temp [17];
        int duplicate_test = 1;
        if(event_index > 0)
            duplicate_test = strcmp(temp, lineStr);
        // remove duplicates that result from button presses in embedded system
        if (duplicate_test != 0)
        {
        //printf("%s\n", lineStr);
        string raw_string(lineStr, 17);
        int hottub_code = stoi(raw_string.substr(0,4));
        int yr = stoi(raw_string.substr(4,2));
        int dy = stoi(raw_string.substr(6,2));
        int mn = stoi(raw_string.substr(8,2));
        int sec = stoi(raw_string.substr(10,2));
        int min = stoi(raw_string.substr(12,2));
        int hr = stoi(raw_string.substr(14,2));
        if (20 <= hr || hr <= 4)
            period_of_day = "night";
        else if (4 <= hr && hr < 12)
            period_of_day = "morning";
        else if (12 <= hr && hr < 20)
            period_of_day = "afternoon";
        int event_flag = stoi(raw_string.substr(16));
        Event* pevent;
        pevent = new Event();
        event_index++;
        strcpy(temp, lineStr);
        pevent -> eventCodes.setCodes(hottub_code, event_flag, period_of_day, event_index);
        pevent -> timeDate.setCalendar(dy, mn, yr);
        pevent -> timeDate.setClock(hr, min, sec);
        list1.insertBeforeFirst(pevent);
        //cout << "packet completed " << transmission << endl;
        }
    }
    
    cout << "All data have been transferred" << endl;
    
    
    //flushSerialData();
    //closeSerialPort();

    int hr1 = 16; int min1 = 30; int sec1 = 00; int dy1 = 12; int mn1 = 5; int yr1 = 16;
    
    int hr2 = 17; int min2 = 00; int sec2 = 00; int dy2 = 16; int mn2 = 5; int yr2 = 16;
    
    //list1.listar();
    
    while(true)
    {
        // infinite loop to display data presentation options to user
        int option;
        cout << "If you wish to consult the data, please choose from the following options:" << endl;
        cout << "1. List all events in a date range" << endl;
        cout << "2. Consult the times of day with greatest control activity"<< endl;
        cout << "3. See the total air-conditiioning usage during a date range" << endl;
        //list1.listar();
        cin  >> option;
        bool valid_date = false;
        switch(option)
        {
                
            case 1:
                // we can leave the loop when we have a valid date; otherwise, we are prompted to enter it again
                while(!valid_date)
                {
                    cout<<"Enter the first date in DD MM YY format:" << endl;
                    cin >> dy1 >> mn1 >> yr1;
                    cout << endl;
                    try{
                        // possible exceptions
                        if( !(dy1 >= 1 && dy1 <= 31) || !(mn1 >= 1 && mn1 <= 12) || !(yr1 >= 0 && yr1 <= 99))
                            throw "Date not valid";
                        else
                            valid_date = true;
                    }
                    catch(const char* exp)
                    {
                        cout << exp << endl;
                        valid_date = false;
                    }
                }
                valid_date = false; // to allow entry into next while
                while(!valid_date)
                {
                    cout<<"Enter the last date in DD MM YY format:" << endl;
                    cin >> dy2 >> mn2 >> yr2;
                    cout << endl;
                    try{
                        // possible exceptions
                        if( !(dy2 >= 1 && dy2 <= 31) || !(mn2 >= 1 && mn2 <= 12) || !(yr2 >= 0 && yr2 <= 99))
                            throw "Date not valid";
                        if(yr2 < yr1)
                            throw "Last date before first date";
                        if((yr2 == yr1) && (mn2 < mn1))
                            throw "Last date before first date";
                        if((yr2 == yr1) && (mn2 == mn1) && (dy2 < dy1))
                            throw "Last date before first date";
                        else
                            valid_date = true;
                    }
                    catch(const char* exp)
                    {
                        cout << exp << endl;
                        valid_date = false;
                    }
                }
                // Once we have valid dates, we pass them to the appropriate "Event" method via a "List" method, which passes all pointers to the "Event" method
                list1.listWithRange(&yr1, &mn1, &dy1, &yr2, &mn2, &dy2);
                break;
            case 2:
                list1.demandByTimeOfDay();
                break;
            case 3:
                while(!valid_date)
                {
                    cout<<"Enter the first date in DD MM YY format:" << endl;
                    cin >> dy1 >> mn1 >> yr1;
                    cout << endl;
                    try{
                        // possible exceptions
                        if( !(dy1 >= 1 && dy1 <= 31) || !(mn1 >= 1 && mn1 <= 12) || !(yr1 >= 0 && yr1 <= 99))
                            throw "Date not valid";
                        
                        else
                            valid_date = true;
                    }
                    catch(const char* exp)
                    {
                        cout << exp << endl;
                        valid_date = false;
                    }
                }
                valid_date = false;
                while(!valid_date)
                {
                    cout<<"Enter the last date in DD MM YY format:" << endl;
                    cin >> dy2 >> mn2 >> yr2;
                    cout << endl;
                    try{
                        // possible exceptions
                        if( !(dy2 >= 1 && dy2 <= 31) || !(mn2 >= 1 && mn2 <= 12) || !(yr2 >= 0 && yr2 <= 99))
                            throw "Date not valid";
                        if(yr2 < yr1)
                            throw "Last date before first date";
                        if((yr2 == yr1) && (mn2 < mn1))
                            throw "Last date before first date";
                        if((yr2 == yr1) && (mn2 == mn1) && (dy2 < dy1))
                            throw "Last date before first date";
                        else
                            valid_date = true;
                    }
                    catch(const char* exp)
                    {
                        cout << exp << endl;
                        valid_date = false;
                    }
                }
                valid_date = false;
                //cout << dy1 << mn1 << yr1 << endl;
                //cout << dy2 << mn2 << yr2 << endl;
                
                list1.totalAirConUse(&yr1, &mn1, &dy1, &yr2, &mn2, &dy2);
                 // Once we have valid dates, we pass them to the appropriate "Event" method via a "List" method, which passes all pointers to the "Event" method
                break;
        }
    }
    
    return 0;
}
