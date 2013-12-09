#include "states.h"


FSM::FSM()
{
	this->current_state = 1; 
	this->last_state = 1;
	this->availableTransitionNames = new std::string[3];
}


void FSM::setCurrentState(int state){
	this->last_state = this->current_state;
	this->current_state = state;
}

int FSM::getCurrentState(){
	return this->current_state;
}



const int* FSM::getAvailableTransitions(){
	return transitions[this->current_state];
}

const std::string* FSM::getAvailableTransitionNames(){
	std::string status;
	if (this->current_state == 0){
		status = failureReasonMessages[this->last_state];
	} else {
		status = transitionlabels[this->current_state][0];
	}

	this->availableTransitionNames[0] = status;
	this->availableTransitionNames[1] = transitionlabels[this->current_state][1];
	this->availableTransitionNames[2] = transitionlabels[this->current_state][2];
	return this->availableTransitionNames;
}


void FSM::chooseFirstTransition(){
	this->setCurrentState(this->getAvailableTransitions()[0]);
}

void FSM::chooseSecondTransition(){
	this->setCurrentState(this->getAvailableTransitions()[1]);
}

const std::string* FSM::getCurrentInfo(){
	return statesInfo[this->current_state];
}