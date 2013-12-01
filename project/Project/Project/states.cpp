#include "states.h"


FSM::FSM()
{
	this->current_state = 1; 
	this->availableTransitionNames = new std::string[2];
}


void FSM::setCurrentState(int state){
	this->current_state = state;
}

int FSM::getCurrentState(){
	return this->current_state;
}

std::string FSM::getCurrentStateName(){
	return statenames[this->current_state];
}

std::string FSM::getCurrentStateFilename(){
	return stateObjFilenames[this->current_state];
}

const int* FSM::getAvailableTransitions(){
	return transitions[this->current_state];
}

const std::string* FSM::getAvailableTransitionNames(){
	const int* possibleTransitions = this->getAvailableTransitions();
	this->availableTransitionNames[0] = statenames[possibleTransitions[0]];
	this->availableTransitionNames[1] = statenames[possibleTransitions[1]];
	return this->availableTransitionNames;
}


void FSM::chooseFirstTransition(){
	this->setCurrentState(this->getAvailableTransitions()[0]);
}

void FSM::chooseSecondTransition(){
	this->setCurrentState(this->getAvailableTransitions()[1]);
}