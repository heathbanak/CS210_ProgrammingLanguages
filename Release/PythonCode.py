#
# PythonCode.py
# CS-210-Project-3
# Heath Banak
# 06-13-22
#
# Last update: 06-19-22
#

import re
import string
import os
import os.path
from os import path

# Create list to be populated
itemList = []

# Add item to list
def AddItem(item):
	itemList.append(item)

# Prints a list of items and amounts sold
def NumItem():
	unique = []

	# Creates a list of unique items
	for itemName in itemList:
		if itemName not in unique:
			unique.append(itemName)

	# Prints list in alphabetical order
	unique.sort()

	for itemName in unique:
		num = 0
		# Get amount of item in list
		num = itemList.count(itemName)
		print(itemName + ": " + str(num))

# Returns amount sold of a passed item
def NumSingleItem(item):
	num = 0

	num = itemList.count(item)

	return num

# Creates a file containing data from item list: item name and amount sold
def FileWrite(filename):
	# Create file if non-existent, otherwise append to file
	file = open(filename, "a")
	
	unique = []
	
	# Creates list of unique items
	for itemName in itemList:
		if itemName not in unique:
			unique.append(itemName)
	
	# Writes items in alphabetical order
	unique.sort()
		
	# If file is empty, populate the file
	if os.stat(filename).st_size == 0:
		for itemName in unique:
			num = 0
			num = itemList.count(itemName)
			file.write(itemName + " " + str(num) + "\n")

	# Close file
	file.close()
