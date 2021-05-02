//
//  States.h
//  
//
//  Created by Ian Downie on 13/03/21.
//

#ifndef States_h
#define States_h


#include <iostream>
#include "AirConState.h"
#include "AirCon.h"

class Idle : public AirConState
{
public:
    void enter(AirCon* p_air) ; // method of actions when entering state
    void toggle(AirCon* p_air) ; // method of actions during state
    void exit(AirCon* p_air) ; // method of actions when exiting state
    static AirConState& getInstance();
};

class Cooling : public AirConState
{
public:
    void enter(AirCon* p_air) ; // method of actions when entering state
    void toggle(AirCon* p_air) ; // method of actions during state
    void exit(AirCon* p_air) ; // method of actions when exiting state
    static AirConState& getInstance();
};








#endif /* States_h */
