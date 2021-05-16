//
//  AirConState.h
//  Pure abstract class that allows us to implement how we transition between states in AirCon and how the states work in States
//
//  Created by Ian Downie on 13/03/21.
//

#ifndef AirConState_h
#define AirConState_h

#include "AirCon.h"

using namespace std;

class AirCon;

class AirConState
{
public:
    virtual void enter(AirCon* p_air) = 0; // method of actions when entering state
    virtual void toggle(AirCon* p_air) = 0; // method of actions during state
    virtual void exit(AirCon* p_air) = 0; // method of actions when exiting state
    virtual ~AirConState() {};
};


#endif /* AirConState_h */
