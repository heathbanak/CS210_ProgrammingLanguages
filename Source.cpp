/*
* Source.cpp
* CS-210-Project-3
* Heath Banak
* 06-13-22
*
* Last update: 06-19-22
*/

#include <Python.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#include "List.h"
#include "Section.h"

/* Python functions */
void CallProcedure(string pName);
int CallFunc(string proc, string param);
int CallFunc(string proc, int param);
/* Main program functions*/
void PrintMenu();
void ListItemAmounts(List &itemList);
void SingleItemAmount(List &itemList);
void PrintHistogram(string filename);

int main() {
	int i;
	int menuChoice;
	List itemList;
	// Known file names are constant
	string const SAMPLEFILE = "Proj3File.txt";
	string const CREATEFILE = "frequency.dat";
	// File in
	ifstream inFS;
	// String to read in file lines
	string textString;
	
	// Open file
	inFS.open(SAMPLEFILE);

	cout << "Opening sample file..." << endl;

	// Print status of file opening
	if (!inFS.is_open()) {
		// Program will not work if file opening fails
		cout << "File opening failed.\n" << endl;
	}
	else {
		cout << "File opened.\n" << endl;
	}

	// Initialize Python
	Py_Initialize();
	
	// Read file into List and Python list
	while (getline(inFS, textString)) {
		CallFunc("AddItem", textString);
		itemList.AddItem(textString);
	}

	// Display user menu
	PrintMenu();

	// Get user input for menu choice
	cout << "Enter a number 1, 2, 3, or 4: ";
	cin >> menuChoice;

	// Run until user chooses to quit
	while (menuChoice != 4) {
		try {
			switch (menuChoice) {
				// List all items and the amounts sold
				case 1:
					cout << "\n-X-\t-X-\t-X-\n" << endl;
					ListItemAmounts(itemList);
					break;
				// Output amount sold of user entered item
				case 2:
					cout << "\n-X-\t-X-\t-X-\n" << endl;
					SingleItemAmount(itemList);
					break;
				// Print histogram of all items sold
				case 3:
					cout << "\n-X-\t-X-\t-X-\n" << endl;
					PrintHistogram(CREATEFILE);
					break;
				// Invalid menu choice
				default:
					throw(menuChoice);
			}
			cout << "\nPress enter to continue...";

			cin.ignore();
			cin.get();

			cout << "\n-X-\t-X-\t-X-\n" << endl;

			PrintMenu();

			cout << "Enter a number 1, 2, 3, or 4: ";
			cin >> menuChoice;
		}
		// Error message displayed when invalid menu choice is entered
		catch (int choice) {
			cout << "\nERROR: INVALID ENTRY" << endl;
			cout << "You Entered: " << choice << endl;
			cout << "Entry must be a number 1, 2, 3, or 4." << endl;
			cout << "Please try again.\n" << endl;
			cout << "Enter a number 1, 2, 3, or 4: ";
			cin >> menuChoice;
		}
	}
	// Once user quits

	cout << "\n-X-\t-X-\t-X-" << endl;

	// End Python
	Py_Finalize();

	cout << "\nClosing file..." << endl;

	// Close file
	inFS.close();

	if (inFS.is_open()) {
		cout << "WARNING: Error closing file" << endl;
	}
	else {
		cout << "File closed." << endl;
	}

	cout << "Goodbye" << endl;

	// End program
	return 0;
}

/*
* Description:
*	To call this function, simply pass the function name in Python that you wish to call.
* Example:
*	callProcedure("printsomething");
* Output:
*	Hello from python!
* Return:
*	None
*/
void CallProcedure(string pName) {
	char* procname = new char[pName.length() + 1];
	strcpy(procname, pName.c_str());

	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);

	delete[] procname;
}

/*
* Description:
*	To call this function, pass the name of the Python function you wish to call and the string parameter you want to send
* Example:
*	int x = CallIntFunc("PrintMe", "Test");
* Output:
*	You sent me: Test
* Return:
*	100 is returned to the C++
*/
int CallFunc(string proc, string param) {
	char* procname = new char[proc.length() + 1];
	strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	strcpy(paramval, param.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	pName = PyUnicode_FromString((char*)"PythonCode");
	pModule = PyImport_Import(pName);
	pDict = PyModule_GetDict(pModule);
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc)) {
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else {
		PyErr_Print();
	}
	Py_DECREF(pValue);
	Py_DECREF(pModule);
	Py_DECREF(pName);

	delete[] procname;
	delete[] paramval;

	return _PyLong_AsInt(presult);
}

/*
* Description:
*	To call this function, pass the name of the Python function you wish to call and the int parameter you want to send
* Example:
*	int x = CallIntFunc("doublevalue", 5);
* Return
*	25 is returned to the C++
*/
int CallFunc(string proc, int param) {
	char* procname = new char[proc.length() + 1];
	strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	pName = PyUnicode_FromString((char*)"PythonCode");
	pModule = PyImport_Import(pName);
	pDict = PyModule_GetDict(pModule);
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc)) {
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else {
		PyErr_Print();
	}

	Py_DECREF(pValue);
	Py_DECREF(pModule);
	Py_DECREF(pName);

	delete[] procname;

	return _PyLong_AsInt(presult);
}

/*
* Description:
*	Prints a formatted user menu
* Example:
*	PrintMenu();
* Output:
*	=======================
*	       USER MENU       
*	=======================
*	1. Sales by Item
*	2. Single Item Sales
*	3. Histogram
*	4. Quit
*	-----------------------
* Return:
*	None
*/
void PrintMenu() {
	Section* menu = new Section("       USER MENU       ");

	menu->PrintTitle();

	cout << "1. Sales by Item" << endl;
	cout << "2. Single Item Sales" << endl;
	cout << "3. Histogram" << endl;
	cout << "4. Quit" << endl;

	menu->EndSection();

	delete menu;

	cout << endl;
}

/*
* Description:
*	Displays a list of all items sold with the amount sold
* Example:
*	ListItemAmounts(myList);
* Output:
*	=====================
*	    SALES BY ITEM    
*	=====================
*	Item 1: 8
*	Item 2: 5
*	---------------------
* Return:
*	None
*/
void ListItemAmounts(List &itemList) {
	Section* listItems = new Section("    SALES BY ITEM    ");

	listItems->PrintTitle();

	CallProcedure("NumItem");

	listItems->EndSection();
}

/*
* Description:
*	Prompts user to enter an item and outputs the number of items sold. If item is not in stock, outputs out of stock message
* Example:
*	SingleItemAmount(myList);
* Output:
*	=========================
*	    SINGLE ITEM SALES    
*	=========================
*	Enter item: item 1
*
*	Item 1: 8
*	-------------------------
* Return:
*	None
*/
void SingleItemAmount(List &itemList) {
	Section* itemSales = new Section("    SINGLE ITEM SALES    ");
	string userItem;
	int returned;

	itemSales->PrintTitle();

	// Get user input of item name
	cout << "Enter item: ";
	cin >> userItem;
	cout << endl;

	// If user entered item is not in item list
	if (!itemList.IsIn(userItem)) {
		cout << "Item Not In Stock" << endl;
	}
	else {
		returned = CallFunc("NumSingleItem", userItem);

		cout << userItem << ": " << returned << endl;
	}
	
	itemSales->EndSection();
}

/*
* Description:
*	Reads a file created in Python of items and amounts sold and outputs a histogram of those items and amounts
* Example:
*	PrintHistogram(newFile.dat);
* Output:
*	=======================
*	       HISTOGRAM       
*	=======================
*	Item 1 >>>>>>>>
*	Item 2 >>>>>
*	-----------------------
* Return:
*	None
*/
void PrintHistogram(string filename) {
	Section* histogram = new Section("       HISTOGRAM       ");
	ifstream inFS;
	string textstring;
	int i;

	histogram->PrintTitle();

	// Creates file in Python containing items and amounts sold
	CallFunc("FileWrite", filename);

	// Reads created file
	inFS.open(filename);

	// For each line in the file
	while (getline(inFS, textstring)) {
		int index;
		string item;
		int num;

		// Find index of space separating item name and amount sold
		index = textstring.find(" ");

		// Get item name
		item = textstring.substr(0, index + 1);

		// Get item amount and convert to int
		num = stoi(textstring.substr(index + 1, 1));

		// Aligns characters for histogram
		cout << setw(13) << setfill(' ') << left << item;

		// Output correct number of characters for histogram
		for (i = 0; i < num; ++i) {
			cout << ">";
		}
		cout << endl;
	}

	histogram->EndSection();
}
