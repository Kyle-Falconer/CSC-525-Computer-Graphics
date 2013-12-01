#ifndef _STATES
#define _STATES

#include <string>

#define NUM_STATES 15

const std::string statenames[NUM_STATES] = {
	"Go Home",			// 0 -> 0, 0
	"Doors",			// 1 -> 2, 3
	"Secretary",		// 2 -> 3, 4
	"Human Resources",	// 3 -> 4, 0
	"Window",			// 4 -> 5, 0
	"Window Cleaner",	// 5 -> 8, 0
	"Main Lobby",		// 6 -> 7, 2
	"Elevator",			// 7 -> 6, 8
	"Second Floor",		// 8 -> 9, 11
	"Food Court",		// 9 -> 10, 11
	"Eat Food",			// 10 -> 9, 0
	"Stairs",			// 11 -> 12, 6
	"Third Floor",		// 12 -> 11, 13
	"Watercooler",		// 13 -> 12, 14
	"Desk"				// 14 -> 14, 14
};

const int transitions[NUM_STATES][2] = {
	{0, 0},
	{2, 3},
	{3, 4},
	{4, 0},
	{5, 0},
	{8, 0},
	{7, 2},
	{6, 8},
	{9, 11},
	{10, 11},
	{9, 0},
	{12, 6},
	{11, 13},
	{12, 14},
	{14, 14}
};

const std::string stateObjFilenames[NUM_STATES] = {
	"home",
	"doors",
	"secretary",
	"hr",
	"window",
	"window_cleaner",
	"lobby",
	"elevator",
	"floor_two",
	"foodcourt",
	"eating",
	"stairs",
	"floor_one",
	"watercooler",
	"desk"
};

class FSM
{
private:
	int current_state;
	std::string* availableTransitionNames;
public: 
	FSM();			
	int FSM::getCurrentState();
	void FSM::setCurrentState(int);
	std::string FSM::getCurrentStateName();
	std::string FSM::getCurrentStateFilename();
	const int* FSM::getAvailableTransitions();
	const std::string* FSM::getAvailableTransitionNames();
	void FSM::chooseFirstTransition();
	void FSM::chooseSecondTransition();

};

#endif