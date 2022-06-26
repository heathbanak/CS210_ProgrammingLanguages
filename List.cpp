/*
* List.cpp
* CS-210-Project-3
* Heath Banak
* 06-16-22
*
* Last update: 06-19-22
*/

#include <string>
#include <vector>
#include <iostream>

using namespace std;

#include "List.h"

// Default constructor
List::List() {
	listSize = itemList.size();
}

// Listsize accessor
size_t List::GetListSize() {
	return listSize;
}

// List item accessor
string List::GetItemAt(int index) {
	return itemList.at(index);
}

// Adds item to list
void List::AddItem(string item) {
	itemList.push_back(item);
	// Listsize is updated as items are added
	listSize = itemList.size();
}

// Checks whether a passed item is in a list and returns true or false
bool List::IsIn(string item) {
	int i;
	bool contains = false;

	for (i = 0; i < itemList.size(); ++i) {
		if (itemList.at(i) == item) {
			contains = true;
			break;
		}
		else {
			contains = false;
		}
	}

	return contains;
}