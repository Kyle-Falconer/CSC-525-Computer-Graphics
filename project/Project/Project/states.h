#ifndef _STATES
#define _STATES

#include <string>

const std::string statenames[] = {
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

#endif