//
//  States.cpp
//  
//
//  Created by Ian Downie on 13/03/21.
//

#include "AirCon.h"
#include "States.h"

AirCon::AirCon()
{
    // We enter here from main and then use this constructor to enter initial state
    //cout << "we're in aircon" << endl;
    currentState = &Idle::getInstance(); // Set initial state to Idle
    currentState->enter(this);
}

void AirCon::setState(AirConState& newState)
{
    currentState->exit(this);
    currentState = &newState;   // Change the state here
    currentState->enter(this);
}

void AirCon::toggle()
{
    // Delegate the task of determining the next state to the current state
    currentState->toggle(this);
}


