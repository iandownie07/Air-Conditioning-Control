//
//  States.cpp
//  
//
//  Created by Ian Downie on 13/03/21.
//

#include "AirCon.h"
#include "States.h"

AirCon::AirCon()
// Constructor for AirCon class to define states
{
    // We enter here from main and then use this constructor to enter initial state
    currentState = &Idle::getInstance(); // Set initial state to Idle
    currentState->enter(this); // Pass a pointer of the current state (Idle) to its enter method
}

void AirCon::setState(AirConState& newState)
// "setState" is called within the finite state machine (FSM) when we wish to change state. New state is determined in FSM
{
    currentState->exit(this);
    currentState = &newState;   // Change the state here
    currentState->enter(this);
}

void AirCon::toggle()
// Generic method that is implemented in specific states so that they determine the next state within their own "toggle" method
{
    // Delegate the task of determining the next state to the current state
    currentState->toggle(this);
}


