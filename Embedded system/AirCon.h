//
//  AirCon.h
//
//
//  Created by Ian Downie on 06/03/21.
//

#ifndef AirCon_h
#define AirCon_h

#include "AirConState.h"

class AirConState; // forward declaration

class AirCon
{
    
    AirConState* currentState;
public:
    AirCon();
    void toggle();
    void setState(AirConState& newState);
};

#endif /* AirCon_h */
