#ifndef _STATES
#define _STATES

#include <string>

#define NUM_STATES 10
#define NUM_INFO_LINES 10


const std::string transitionlabels[NUM_STATES][3] = {
	{"", "Press F5 to restart.", "Press Esc to quit."},		// home
	{"You see the front door.", "1 - Enter the front doors.", "2 - Get back in your car and leave."}, // doors
	{"You see a receptionist, who suggests that you speak to H.R.", "1 - Talk to Human Resources.", "2 - Ignore the receptionist and climb out the window."},	// secretary
	{"The Human Resources lady looks angry.", "1 - Talk to her.", "2 - Climb out the window."},	// HR
	{"You poke your head out the window and see a ladder.", "1 - Climb up to the second floor.","2 - Climb down to the parking lot."},	// Window
	{"You are on the second floor and see a corridor with labeled entrances.","1 - Visit the food court.", "2 - Go to the stair well."}, // 2nd floor
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

const std::string failureReasonMessages[NUM_STATES] = {
	"You left the office without doing any work and have been fired.",
	"Your boss saw you leave without working and have now been fired.",
	"",
	"You have been eaten by a grue.",
	"",
	"",
	"You ate a rotten hot dog and now have food poisoning.",
	"",
	"",
	""
};

const std::string statesInfo[NUM_STATES][NUM_INFO_LINES] = {
	// 37 characters long:
	// "0123456789012345789012345678901234890"

	// Home
	{ "This game was created by",
	  "      Brett Story and Kyle Falconer   ",
	  "For the:",
	  "       Computer Science Department    ",
	  "                   at               ",
	  "        Missouri State University   ",
	  "",
	  "Basic 3D models were obtained through",
	  "the Trimble 3D Warehouse",
	  "http://sketchup.google.com/3dwarehouse/"},

	// Front Doors
	{ "Welcome to your first day at work as a",
	  "Software Engineer!",
	  "It looks like there is some ",
	  "construction going on and the elevator ",
	  "is out. You will have to find your way ",
	  "to your desk using another path.",
	  "",
	  "",
	  "",
	  ""},

	// Reception
	{"The average salary of a Software",
	  "Engineer with a Computer Science",
	  "degree is $90,000.",
	  "(2013, indeed.com)",
	  "",
	  "",
	  "",
	  "",
	  "",
	  ""},

	// Human Resouces
	{ "",
	  "",
	  "",
	  "",
	  "",
	  "",
	  "",
	  "",
	  "",
	  ""},

	// Window
	{ "Speaking of windows, Microsoft Windows",
	  "is just one example of the many",
	  "programs made by Software Engineers",
	  "and Computer Scientists.",
	  "",
	  "",
	  "",
	  "",
	  "",
	  ""},

	// Second Floor
	{ "",
	  "",
	  "",
	  "",
	  "",
	  "",
	  "",
	  "",
	  "",
	  ""},

	// Food Court
	{ "Many software companies go to great",
	  "lengths to make sure their employees",
	  "are happy, healthy, and comfortable.",
	  "Many companies, like Google and Apple",
	  "have on-site cafeterias, fitness",
	  "centers, laundry, daycare, and other",
	  "amenities.",
	  "",
	  "",
	  ""},

	// Stairs
	{ "",
	  "",
	  "",
	  "",
	  "",
	  "",
	  "",
	  "",
	  "",
	  ""},

	// Third Floor
	{ "",
	  "",
	  "",
	  "",
	  "",
	  "",
	  "",
	  "",
	  "",
	  ""},

	// Desk
	{ "",
	  "",
	  "",
	  "",
	  "",
	  "",
	  "",
	  "",
	  "",
	  ""}
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
	const std::string* FSM::getCurrentInfo();
};

#endif
