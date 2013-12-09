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
	{ "Software Developers often only",
	  "require a Bachelor's Degree to",
	  "obtain a high quality job.",
	  "(BLS.gov, 2012)",
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
	{ "Job outlooks for Software Engineers",
	  "are over double that of job outlooks",
	  "for all occupations that the Bureau",
	  "of Labor Statistics tracks.",
	  "(BLS.gov, 2012)",
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
	{ "On the subject of moving up, job",
	  "outlooks for Software Engineers are",
	  "over double that of job outlooks for",
	  "all occupations that the Bureau of",
	  "Labor Statistics tracks.",
	  "(BLS.gov, 2012)",
	  "",
	  "",
	  ""},

	// Third Floor
	{ "This game is a simple representation",
	  "of something called a Finite State ",
	  "Machine (FSM). Each \"state\", like",
	  "this one, has two choices, also called",
	  "\"transitions\" or \"paths\". A FSM",
	  "is just one of the many kinds of ",
	  "tools used by Computer Scientists when",
	  "trying to solve complex problems.",
	  "",
	  ""},

	// Desk
	{ "As a Software Developer, you will",
	  "almost always have a desk to sit at,",
	  "since unemployment for the field sit",
	  "at about 4%, nearly half of the",
	  "national unemployment rate.",
	  "(USNews.com, 2013)",
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
