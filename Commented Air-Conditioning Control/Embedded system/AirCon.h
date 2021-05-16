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
// The forward declaration is necessary because, at compilation, if AirConState hasn't been compiled and we create a variable of that type in AirCon, there will be an error.

class AirCon
{
    
    AirConState* currentState;
public:
    AirCon();
    void toggle();
    void setState(AirConState& newState);
};

#endif /* AirCon_h */
