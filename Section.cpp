/*
* Section.cpp
* CS-210-Project-3
* Heath Banak
* 06-19-22
*
* Last update: 06-19-22
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#include "Section.h"

// Default constructor
Section::Section() {
	title = "";
	titleLen = title.size();
}

// Constructor with user entered title
Section::Section(string newTitle) {
	title = newTitle;
	titleLen = title.size();
}

// Prints formatted title
void Section::PrintTitle() {
	cout << setw(titleLen) << setfill('=') << "" << endl;
	cout << title << endl;
	cout << setw(titleLen) << "" << endl;
}

// Prints a line to visually end section
void Section::EndSection() {
	for (i = 0; i < titleLen; ++i) {
		cout << "-";
	}
}