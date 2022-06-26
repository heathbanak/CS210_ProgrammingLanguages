/*
* List.h
* CS-210-Project-3
* Heath Banak
* 06-16-22
*
* Last update: 06-19-22
*/

#ifndef List_h
#define List_h

#include <vector>
#include <string>

using namespace std;

class List {
	public:
		List(); // Default constructor	
		size_t GetListSize(); // Listsize accessor
		string GetItemAt(int index); // List item accessor
		void AddItem(string item); // Add item to list
		bool IsIn(string item); // Check if list contains a passed item
	private:
		vector<string> itemList;
		size_t listSize;
};

#endif /* LIST_H */

