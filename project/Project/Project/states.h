#ifndef _STATES
#define _STATES

#include <string>

#define NUM_STATES 10


const std::string transitionlabels[NUM_STATES][3] = {
	{"You left the office without doing any work and have been fired.", "", ""},		// home
	{"You see the front door.", "1 - Enter the front doors.", "2 - Get back in your car and leave."}, // doors
	{"You see a receptionist, who suggests that you speak to H.R.", "1 - Talk to Human Resources.", "2 - Ignore the receptionist and climb out the window."},	// secretary
	{"The Human Resources lady looks angry.", "1 - Talk to her.", "2 - Climb out the window."},	// HR
	{"You poke your head out the window and see a ladder.", "1 - Climb up to the second floor.","2 - Climb down to the parking lot."},	// Window
	{"You are on the second floor and see a corridor with labels at various entrance ways.","1 - Visit the food court.", "2 - Go to the stair well."}, // 2nd floor
	{"You are now at the food court and see the stair well again in the distance.","1 - Eat some food.", "2 - Go to the stair well."}, // food court
	{"You are standing in the stair well.","1 - Go up the stairs.", "2 - Go down the stairs."},
	{"You are now on the third floor, back on familiar ground.","1 - Go to your desk.", "2 - Go back down the stairs."},
	{"You made it to your desk!", "", ""}
};

const int transitions[NUM_STATES][2] = {
	{0, 0},
	{2, 0},
	{3, 4},
	{0, 4},
	{5, 1},
	{6, 7},
	{0, 7},
	{8, 2},
	{9, 7},
	{9, 9}
};



class FSM
{
private:
	int current_state;
	int last_state;
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