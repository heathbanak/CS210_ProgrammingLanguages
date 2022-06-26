/*
* Section.h
* CS-210-Project-3
* Heath Banak
* 06-19-22
*
* Last update: 6-19-22
*/

#ifndef Section_h
#define Section_h

#include <string>

using namespace std;

class Section {
	public:
		Section(); // Default constructor
		Section(string newTitle); // Constructor with user entered title
		void PrintTitle(); // Prints formatted title
		void EndSection(); // Prints line to visually end section
	private:
		string title;
		size_t titleLen;
		int i; 
};

#endif /* Section_h */
