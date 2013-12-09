/*
  Copyright 2013 Brett Story and Kyle Falconer

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

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